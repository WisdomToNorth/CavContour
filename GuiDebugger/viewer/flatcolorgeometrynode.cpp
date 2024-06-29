#include "flatcolorgeometrynode.h"

namespace debugger
{
FlatColorGeometryNode::FlatColorGeometryNode(const DrawStyle &drawstyle)
    : draw_style_(drawstyle)
{
    auto geotype =
        drawstyle.useUInt32Index ? QSGGeometry::UnsignedIntType : QSGGeometry::UnsignedShortType;

    setGeometry(new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), 0, 0, geotype));
    setMaterial(new QSGFlatColorMaterial);

    auto qsg_geometry_ = geometry();
    qsg_geometry_->setDrawingMode(draw_style_.linetype);
    qsg_geometry_->setLineWidth(draw_style_.width);

    auto material_ = static_cast<QSGFlatColorMaterial *>(material());
    material_->setColor(draw_style_.color);
}

FlatColorGeometryNode::~FlatColorGeometryNode()
{
    auto material_ = static_cast<QSGFlatColorMaterial *>(material());
    delete material_;
    delete geometry();
}

DrawStyle &FlatColorGeometryNode::drawStyle()
{
    return draw_style_;
}

void FlatColorGeometryNode::updateDrawStyle(const DrawStyle &drawstyle)
{
    auto qsg_geometry_ = geometry();
    bool geo_dirty = false;
    if (drawstyle.useUInt32Index != draw_style_.useUInt32Index)
    {
        draw_style_.useUInt32Index = drawstyle.useUInt32Index;
        // TODO: not able to set index type
        geo_dirty = true;
    }
    if (drawstyle.linetype != draw_style_.linetype)
    {
        draw_style_.linetype = drawstyle.linetype;
        qsg_geometry_->setDrawingMode(drawstyle.linetype);
        geo_dirty = true;
    }
    if (drawstyle.width != draw_style_.width)
    {
        draw_style_.width = drawstyle.width;
        qsg_geometry_->setLineWidth(drawstyle.width);
        geo_dirty = true;
    }
    if (geo_dirty)
    {
        markDirty(QSGNode::DirtyStateBit::DirtyGeometry);
    }

    auto material_ = static_cast<QSGFlatColorMaterial *>(material());
    if (material_->color() != drawstyle.color)
    {
        material_->setColor(drawstyle.color);
        markDirty(QSGNode::DirtyStateBit::DirtyMaterial);
    }

    if (drawstyle.visible != draw_style_.visible)
    {
        draw_style_.visible = drawstyle.visible;
        markDirty(QSGNode::DirtySubtreeBlocked);
    }
}

bool FlatColorGeometryNode::isSubtreeBlocked() const
{
    return !draw_style_.visible;
}
} // namespace debugger
