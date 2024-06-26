#include "simplecirclenode.h"

#include <cmath>

namespace debugger
{
namespace internal
{
template <typename Real>
constexpr Real pi()
{
    return Real(3.14159265358979323846264338327950288);
}

template <typename Real>
constexpr Real tau()
{
    return Real(2) * pi<Real>();
}
} // namespace internal

SimpleCircleNode::SimpleCircleNode(const DrawStyle &drawstyle)
    : GeoNode(drawstyle)
{
    // DrawStyle style = this->draw_style_;
    // style.linetype = QSGGeometry::DrawTriangleFan;
    // updateDrawStyle(style);
}

void SimpleCircleNode::setGeometry(qreal x, qreal y, qreal radius)
{
    center_x = x;
    center_y = y;
    radius_ = radius;
}

void SimpleCircleNode::update()
{
    int surroundingVertexes = 12;
    int vertexCount = surroundingVertexes + 1;
    auto &qsg_geometry_ = *geometry();
    qsg_geometry_.allocate(vertexCount, vertexCount);
    std::uint32_t *segVertexIndices = qsg_geometry_.indexDataAsUInt();
    for (int i = 0; i < vertexCount; ++i)
    {
        segVertexIndices[i] = static_cast<std::uint32_t>(i);
    }

    QSGGeometry::Point2D *vertexData = qsg_geometry_.vertexDataAsPoint2D();
    for (int i = 1; i <= vertexCount; ++i)
    {
        double angle = internal::tau<double>() * static_cast<double>(i - 1) /
                       static_cast<double>(surroundingVertexes);
        vertexData[i - 1].set(center_x + radius_ * std::cos(angle),
                              center_y + radius_ * std::sin(angle));
    }
    markDirty(QSGNode::DirtyGeometry);
}
} // namespace debugger
