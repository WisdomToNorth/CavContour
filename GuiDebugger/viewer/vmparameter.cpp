#include "vmparameter.h"

#include <cmath>

namespace debugger
{
void VMParameterUtils::PlineToSPline(const Pline &pline, SPline &spline)
{
    spline.clear();
    // TODO
}

VMParameter VMParameterUtils::fromBulge(const double x0, const double y0, const double x1,
                                        const double y1, const double bulge)
{
    VMParameter parameter;
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

void VMParameterUtils::SPlineToPline(const SPline &spline, Pline &pline)
{
    pline.clear();
    VMParameter segment;
    for (size_t i = 0; i < spline.size() - 1; i++)
    {
        segment =
            fromBulge(spline[i].x, spline[i].y, spline[i + 1].x, spline[i + 1].y, spline[i].bulge);
        pline.push_back(segment);
    }
}
} // namespace debugger
