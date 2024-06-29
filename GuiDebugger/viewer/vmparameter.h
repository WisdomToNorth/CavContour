#ifndef VM_PARAMETER_H
#define VM_PARAMETER_H

#include <vector>

namespace debugger
{
struct VMParameter
{
    double x0 = 0.0;
    double y0 = 0.0;
    double x1 = 0.0;
    double y1 = 0.0;
    double center_x = 0.0;
    double center_y = 0.0;
    double radius = 0.0;
    bool is_ccw = true;
    bool is_line = true;
};

struct VMSimpleParameter
{
    double x = 0.0;
    double y = 0.0;
    double bulge = 0.0;
};

typedef VMParameter Segment;
typedef std::vector<VMParameter> Pline;
typedef std::vector<VMSimpleParameter> SPline;
typedef std::vector<Pline> ViewData;

class VMParameterUtils
{
public:
    static void PlineToSPline(const Pline &pline, SPline &spline);
    static void SPlineToPline(const SPline &spline, Pline &pline);

private:
    static VMParameter fromBulge(const double x0, const double y0, const double x1, const double y1,
                                 const double bulge);
};

} // namespace debugger
#endif // VM_PARAMETER_H
