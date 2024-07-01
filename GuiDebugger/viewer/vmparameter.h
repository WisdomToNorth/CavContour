#ifndef VM_PARAMETER_H
#define VM_PARAMETER_H

#include <vector>

namespace debugger
{
struct DirF
{
    double x_;
    double y_;
    static DirF rotateFor(const DirF &dir, double angle_in_radian);
    static DirF normalized(const DirF &dir);
    double cross(const DirF &dir) const
    {
        return x_ * dir.y_ - y_ * dir.x_;
    }
    double dot(const DirF &dir) const
    {
        return x_ * dir.x_ + y_ * dir.y_;
    }
    double norm() const;
    static double angleAcute(const DirF &dir1, const DirF &dir2);
    DirF normalized() const
    {
        return normalized(*this);
    }
    DirF negate() const
    {
        return DirF{-x_, -y_};
    }
};

struct RecordF
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

public:
    DirF getOutDir(bool head) const;
    void reverse()
    {
        std::swap(x0, x1);
        std::swap(y0, y1);
        is_ccw = !is_ccw;
    }
};

struct SRecordF
{
    double x = 0.0;
    double y = 0.0;
    double bulge = 0.0;
};

typedef std::vector<RecordF> Pline;
typedef std::vector<SRecordF> SPline;

typedef std::vector<Pline> ViewData;

class PlineUtils
{
public:
    static void SPlineToPline(const SPline &spline, Pline &pline);
    static void PlineToSPline(const Pline &, SPline &);

    static RecordF fromBulge(const double x0, const double y0, const double x1, const double y1,
                             const double bulge);
    static SRecordF toBulge(const RecordF &record);
    static RecordF moveEndpoint(const RecordF &record, bool move_head, double newX, double newY);
};

} // namespace debugger
#endif // VM_PARAMETER_H
