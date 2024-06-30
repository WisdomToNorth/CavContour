#include "GeoNode.h"

namespace debugger
{
GeoNode::GeoNode(const DrawStyle &drawstyle)
    : draw_style_(drawstyle)
{
    auto geotype =
        drawstyle.useUInt32Index ? QSGGeometry::UnsignedIntType : QSGGeometry::UnsignedShortType;

    QSGGeometry *geometry =
        new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), 0, 0, geotype);
    setGeometry(geometry);
    geometry->setDrawingMode(draw_style_.linetype);
    geometry->setLineWidth(draw_style_.width);
    this->setFlag(QSGNode::OwnsGeometry);

    QSGFlatColorMaterial *material = new QSGFlatColorMaterial();
    material->setColor(draw_style_.color);
    setMaterial(material);
    this->setFlag(QSGNode::OwnsMaterial);
}

GeoNode::~GeoNode()
{
}

DrawStyle &GeoNode::drawStyle()
{
    return draw_style_;
}

void GeoNode::updateDrawStyle(const DrawStyle &drawstyle)
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

bool GeoNode::isSubtreeBlocked() const
{
    return !draw_style_.visible;
}
} // namespace debugger
