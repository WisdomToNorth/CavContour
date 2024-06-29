#ifndef SIMPLECIRCLENODE_H
#define SIMPLECIRCLENODE_H

#include "flatcolorgeometrynode.h"
#
namespace debugger
{
class SimpleCircleNode : public FlatColorGeometryNode
{
public:
    SimpleCircleNode(const DrawStyle &drawstyle);
    void setGeometry(qreal x, qreal y, qreal radius);
    void update() override;

private:
    qreal m_radius;
    qreal m_xPos;
    qreal m_yPos;
};
} // namespace debugger

#endif // SIMPLECIRCLENODE_H
