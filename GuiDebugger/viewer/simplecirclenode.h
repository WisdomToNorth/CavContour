#ifndef SIMPLECIRCLENODE_H
#define SIMPLECIRCLENODE_H

#include "GeoNode.h"
#
namespace debugger
{
class SimpleCircleNode : public GeoNode
{
public:
    SimpleCircleNode(const DrawStyle &drawstyle);
    void setGeometry(qreal x, qreal y, qreal radius);
    void update() override;

private:
    qreal radius_;
    qreal center_x;
    qreal center_y;
};
} // namespace debugger

#endif // SIMPLECIRCLENODE_H
