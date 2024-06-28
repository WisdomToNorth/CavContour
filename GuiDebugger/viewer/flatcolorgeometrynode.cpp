#include "flatcolorgeometrynode.h"

namespace debugger
{
FlatColorGeometryNode::FlatColorGeometryNode(bool useUInt32Index)
    : visible_(true)
    , qsg_geometry_(QSGGeometry::defaultAttributes_Point2D(), 0, 0,
                    useUInt32Index ? QSGGeometry::UnsignedIntType : QSGGeometry::UnsignedShortType)
{
    qsg_geometry_.setLineWidth(style_.width);
    qsg_geometry_.setDrawingMode(style_.mode);
    setGeometry(&qsg_geometry_);

    material_.setColor(style_.color);
    setMaterial(&material_);
}

const QColor &FlatColorGeometryNode::color() const
{
    return style_.color;
}

void FlatColorGeometryNode::setColor(const QColor &color)
{
    style_.color = color;
    material_.setColor(style_.color);

    markDirty(QSGNode::DirtyMaterial);
}

bool FlatColorGeometryNode::isVisible() const
{
    return visible_;
}

void FlatColorGeometryNode::setIsVisible(bool isVisible)
{
    if (visible_ != isVisible)
    {
        visible_ = isVisible;
        markDirty(QSGNode::DirtySubtreeBlocked);
    }
}

bool FlatColorGeometryNode::isSubtreeBlocked() const
{
    return !visible_;
}
} // namespace debugger
