#ifndef GEONODE_H
#define GEONODE_H

#include <QSGFlatColorMaterial>
#include <QSGGeometryNode>

#include "drawstyle.h"

namespace debugger
{
class GeoNode : public QSGGeometryNode
{
public:
    GeoNode(const DrawStyle &drawstyle);
    ~GeoNode() override;
    DrawStyle &drawStyle();
    void updateDrawStyle(const DrawStyle &drawstyle);
    bool isSubtreeBlocked() const override;
    virtual void update() = 0;

protected:
    DrawStyle draw_style_;
};
} // namespace debugger
#endif // FLATCOLORGEOMETRYNODE_H
