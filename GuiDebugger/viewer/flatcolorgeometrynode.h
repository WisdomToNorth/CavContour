#ifndef FLATCOLORGEOMETRYNODE_H
#define FLATCOLORGEOMETRYNODE_H

#include <QSGFlatColorMaterial>
#include <QSGGeometryNode>

#include "drawstyle.h"
namespace debugger
{
class FlatColorGeometryNode : public QSGGeometryNode
{
public:
    FlatColorGeometryNode(const DrawStyle &drawstyle);
    ~FlatColorGeometryNode() override;
    DrawStyle &drawStyle();
    void updateDrawStyle(const DrawStyle &drawstyle);
    bool isSubtreeBlocked() const override;
    virtual void update() = 0;

protected:
    DrawStyle draw_style_;
};
} // namespace debugger
#endif // FLATCOLORGEOMETRYNODE_H
