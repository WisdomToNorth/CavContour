#ifndef PLINESEGMENTNODE_H
#define PLINESEGMENTNODE_H

#include "viewer/GeoNode.h"

#include "drawstyle.h"
#include "vmparameter.h"

namespace debugger
{
class SegmentNode : public GeoNode
{
public:
    SegmentNode(const DrawStyle &drawstyle);
    void setData(const RecordF &segment);
    void update() override;

private:
    void drawArc(const double &p1_x, const double &p1_y, const double &p2_x, const double &p2_y,
                 const double &center_x, const double &center_y, const double &radius, bool ccw,
                 double arcApproxError);
    void drawLine(const QPointF &p1, const QPointF &p2);
    void drawLine(const double &p1_x, const double &p1_y, const double &p2_x, const double &p2_y);

private:
    RecordF data_;
};
} // namespace debugger
#endif // PLINESEGMENTNODE_H
