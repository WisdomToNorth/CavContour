#include "vmparameter.h"

#include <cassert>
#include <cmath>
#include <iostream>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#define M_PI_2 1.57079632679489661923
#endif

namespace debugger
{

RecordF PlineUtils::fromBulge(const double x0, const double y0, const double x1, const double y1,
                              const double bulge)
{
    RecordF parameter;
    parameter.x0 = x0;
    parameter.y0 = y0;
    parameter.x1 = x1;
    parameter.y1 = y1;
    if (std::abs(bulge - 0.0) < 1e-6)
    {
        parameter.is_line = true;
        return parameter;
    }
    else
    {
        double b = std::abs(bulge);
        double dx = x1 - x0;
        double dy = y1 - y0;
        double d = std::sqrt(dx * dx + dy * dy);

        double radius = d * (b * b + 1.0) / (4.0 * b);
        double s = b * d / 2.0;
        double m = radius - s;
        double offs_x = -m * dy / d;
        double offs_y = m * dx / d;
        if (bulge < 0)
        {
            offs_x = -offs_x;
            offs_y = -offs_y;
        }
        double cx = x0 + dx / 2.0 + offs_x;
        double cy = y0 + dy / 2.0 + offs_y;
        bool is_ccw = bulge > 0;

        parameter.center_x = cx;
        parameter.center_y = cy;
        parameter.radius = radius;
        parameter.is_ccw = is_ccw;
        parameter.is_line = false;
        return parameter;
    }
}

SRecordF PlineUtils::toBulge(const RecordF &record)
{
    SRecordF parameter;
    parameter.x = record.x0;
    parameter.y = record.y0;

    if (record.is_line)
    {
        parameter.bulge = 0.0;
        return parameter;
    }
    else
    {
        double dx = record.x1 - record.x0;
        double dy = record.y1 - record.y0;
        double d = std::sqrt(dx * dx + dy * dy);

        double radius = record.radius;
        double s = radius - std::sqrt(radius * radius - (d / 2.0) * (d / 2.0));
        double bulge = 2 * s / d;

        if (!record.is_ccw)
        {
            bulge = -bulge;
        }

        parameter.bulge = bulge;
        return parameter;
    }
}

void PlineUtils::PlineToSPline(const Pline &, SPline &)
{
    // TODO:
    std::cerr << "PlineToSPline not implemented" << std::endl;
}

void PlineUtils::SPlineToPline(const SPline &spline, Pline &pline)
{
    pline.clear();
    RecordF segment;
    for (size_t i = 0; i < spline.size() - 1; i++)
    {
        segment =
            fromBulge(spline[i].x, spline[i].y, spline[i + 1].x, spline[i + 1].y, spline[i].bulge);
        pline.push_back(segment);
    }
}

DirF DirF::rotateFor(const DirF &dir, double angle_in_radian)
{
    double x = dir.x_ * cos(angle_in_radian) - dir.y_ * sin(angle_in_radian);
    double y = dir.x_ * sin(angle_in_radian) + dir.y_ * cos(angle_in_radian);
    return DirF(x, y);
}

DirF DirF::normalized(const DirF &dir)
{
    double length = sqrt(dir.x_ * dir.x_ + dir.y_ * dir.y_);
    assert(std::abs(length - 0) > 1e-6);
    return DirF(dir.x_ / length, dir.y_ / length);
}

double DirF::norm() const
{
    return std::sqrt(x_ * x_ + y_ * y_);
}
double DirF::angleAcute(const DirF &dir1, const DirF &dir2)
{
    double dot = dir1.dot(dir2) / (dir1.norm() * dir2.norm());
    double angle = acos(dot);              // This will return a value from 0 to pi
    angle = std::min(angle, M_PI - angle); // Limit the angle to the range [0, π/2]
    return angle;
}

DirF RecordF::getOutDir(bool head) const
{
    if (this->is_line)
    {
        if (head)
        {
            return DirF::normalized(DirF(x1 - x0, y1 - y0));
        }
        else
        {
            return DirF::normalized(DirF(x0 - x1, y0 - y1));
        }
    }
    else
    {
        double angle_rad = this->is_ccw ? M_PI / 2 : -M_PI / 2;
        if (head)
        {
            return DirF::rotateFor(DirF(x0 - center_x, y0 - center_y), angle_rad);
        }
        else
        {
            return DirF::rotateFor(DirF(x1 - center_x, y1 - center_y), angle_rad);
        }
    }
}

static RecordF createArcByTwoPntNDir(const double x0, const double y0, const double x1,
                                     const double y1, const DirF &start_dir)
{
    RecordF record;
    record.x0 = x0;
    record.y0 = y0;
    record.x1 = x1;
    record.y1 = y1;
    record.is_line = false;

    double dist_ab = sqrt((x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0));
    double dist_am = dist_ab / 2.0;

    DirF dir_ab(x1 - x0, y1 - y0);
    record.is_ccw = dir_ab.cross(start_dir) < 0;
    double angle = DirF::angleAcute(dir_ab, start_dir);
    double radius = dist_am / sin(angle);
    record.radius = radius;
    double rot_angle = record.is_ccw ? M_PI_2 : -M_PI_2;

    DirF a_c = DirF::rotateFor(start_dir, rot_angle);
    record.center_x = x0 + a_c.x_ * radius;
    record.center_y = y0 + a_c.y_ * radius;

    return record;
}

RecordF PlineUtils::moveEndpoint(const RecordF &record, bool move_head, double newX, double newY)
{
    RecordF updatedRecord = record;
    if (move_head)
    {
        updatedRecord.x0 = newX;
        updatedRecord.y0 = newY;
    }
    else
    {
        updatedRecord.x1 = newX;
        updatedRecord.y1 = newY;
    }

    if (!record.is_line)
    {
        if (move_head)
        {
            DirF end_dir = record.getOutDir(false).normalized().negate();
            updatedRecord = createArcByTwoPntNDir(updatedRecord.x1, updatedRecord.y1,
                                                  updatedRecord.x0, updatedRecord.y0, end_dir);
            updatedRecord.reverse();
        }
        else
        {
            DirF start_dir = record.getOutDir(true).normalized();
            updatedRecord = createArcByTwoPntNDir(updatedRecord.x0, updatedRecord.y0,
                                                  updatedRecord.x1, updatedRecord.y1, start_dir);
        }
    }

    return updatedRecord;
}
} // namespace debugger
