#include "segmentnode.h"

#include <cassert>
#include <cmath>

#include <QSGGeometry>

#include "viewer/graphicshelpers.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

namespace debugger
{

namespace
{
double pointDist(const double &x1, const double &y1, const double &x2, const double &y2)
{
    return std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2));
}

bool validArc(const double &p1_x, const double &p1_y, const double &p2_x, const double &p2_y,
              const double &center_x, const double &center_y, const double &radius, bool ccw)
{
    double dist_p1_center = pointDist(p1_x, p1_y, center_x, center_y);
    double dist_p2_center = pointDist(p2_x, p2_y, center_x, center_y);
    if (std::abs(dist_p1_center - radius) > 1e-6 || std::abs(dist_p2_center - radius) > 1e-6)
    {
        return false;
    }
    return true;
}

double angleFromCenter(const double &center_x, const double &center_y, const double &point_x,
                       const double &point_y)
{
    return std::atan2(point_y - center_y, point_x - center_x);
}

double angleFromCenter(const QPointF &center, const QPointF &point)
{
    return angleFromCenter(center.x(), center.y(), point.x(), point.y());
}

double arcAngle(double angle1, double angle2, bool ccw)
{
    if (ccw)
    {
        if (angle1 < angle2)
        {
            return angle2 - angle1;
        }
        return 2.0 * M_PI - angle1 + angle2;
    }
    else
    {
        if (angle1 > angle2)
        {
            return angle1 - angle2;
        }
        return 2.0 * M_PI - angle2 + angle1;
    }
}
} // namespace

SegmentNode::SegmentNode(const DrawStyle &drawstyle)
    : FlatColorGeometryNode(drawstyle)
{
}

void SegmentNode::setData(const Segment &segment)
{
    data_ = segment;
}

void SegmentNode::update()
{
    if (data_.is_line)
    {
        drawLine(data_.x0, data_.y0, data_.x1, data_.y1);
    }
    else
    {
        drawArc(data_.x0, data_.y0, data_.x1, data_.y1, data_.center_x, data_.center_y,
                data_.radius, data_.is_ccw, draw_style_.arcApproxError);
    }
}

void SegmentNode::drawLine(const double &p1_x, const double &p1_y, const double &p2_x,
                           const double &p2_y)
{
    QSGGeometry &qsg_geometry_ = *geometry();
    qsg_geometry_.allocate(2);
    qsg_geometry_.vertexDataAsPoint2D()[0].set(static_cast<float>(p1_x), static_cast<float>(p1_y));
    qsg_geometry_.vertexDataAsPoint2D()[1].set(static_cast<float>(p2_x), static_cast<float>(p2_y));

    markDirty(QSGNode::DirtyGeometry);
}

void SegmentNode::drawLine(const QPointF &p1, const QPointF &p2)
{
    return drawLine(p1.x(), p1.y(), p2.x(), p2.y());
}

void SegmentNode::drawArc(const double &p1_x, const double &p1_y, const double &p2_x,
                          const double &p2_y, const double &center_x, const double &center_y,
                          const double &radius, bool ccw, double arcApproxError)
{
    assert(validArc(p1_x, p1_y, p2_x, p2_y, center_x, center_y, radius, ccw));
    double dist_p1_p2 = pointDist(p1_x, p1_y, p2_x, p2_y);
    if (dist_p1_p2 < arcApproxError)
    {
        return drawLine(p1_x, p1_y, p2_x, p2_y);
    }

    double startAngle = angleFromCenter(QPointF(center_x, center_y), QPointF(p1_x, p1_y));
    double endAngle = angleFromCenter(QPointF(center_x, center_y), QPointF(p2_x, p2_y));
    double deltaAngle = arcAngle(startAngle, endAngle, ccw);

    double segmentSubAngle = std::abs(2.0 * std::acos(1.0 - arcApproxError / radius));
    std::size_t segmentCount = static_cast<std::size_t>(std::ceil(deltaAngle / segmentSubAngle));
    // update segment subangle for equal length segments
    segmentSubAngle = deltaAngle / segmentCount;

    QSGGeometry &qsg_geometry_ = *geometry();
    qsg_geometry_.allocate(static_cast<int>(segmentCount + 1));

    for (std::size_t i = 0; i <= segmentCount; ++i)
    {
        double angle = i * segmentSubAngle + startAngle;
        qsg_geometry_.vertexDataAsPoint2D()[i].set(
            static_cast<float>(radius * std::cos(angle) + center_x),
            static_cast<float>(radius * std::sin(angle) + center_y));
    }

    markDirty(QSGNode::DirtyGeometry);
}

} // namespace debugger
