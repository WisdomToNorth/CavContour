#include "vmparameter.h"

#include <cmath>
#include <iostream>

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

RecordF PlineUtils::moveEndpoint(const RecordF &record, bool moveFirstEndpoint, double newX,
                                 double newY)
{
    RecordF updatedRecord = record;

    if (record.is_line)
    {
        if (moveFirstEndpoint)
        {
            updatedRecord.x0 = newX;
            updatedRecord.y0 = newY;
        }
        else
        {
            updatedRecord.x1 = newX;
            updatedRecord.y1 = newY;
        }
    }
    else
    {
        if (moveFirstEndpoint)
        {
            updatedRecord.x0 = newX;
            updatedRecord.y0 = newY;
        }
        else
        {
            updatedRecord.x1 = newX;
            updatedRecord.y1 = newY;
        }

        // Recalculate radius and center
        double dx = updatedRecord.x1 - updatedRecord.x0;
        double dy = updatedRecord.y1 - updatedRecord.y0;
        double d = std::sqrt(dx * dx + dy * dy);

        double radius = record.radius;
        double s = std::sqrt(radius * radius - (d / 2.0) * (d / 2.0));
        double b = 2 * s / d;

        double m = radius - s;
        double offs_x = -m * dy / d;
        double offs_y = m * dx / d;
        if (!record.is_ccw)
        {
            offs_x = -offs_x;
            offs_y = -offs_y;
        }

        updatedRecord.center_x = updatedRecord.x0 + dx / 2.0 + offs_x;
        updatedRecord.center_y = updatedRecord.y0 + dy / 2.0 + offs_y;
        updatedRecord.radius = radius;
    }

    return updatedRecord;
}
} // namespace debugger
