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
typedef VMParameter Segment;
typedef std::vector<VMParameter> Pline;
typedef std::vector<Pline> ViewData;

} // namespace debugger
#endif // VM_PARAMETER_H
