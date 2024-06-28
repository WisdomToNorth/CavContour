#ifndef FLATCOLORGEOMETRYNODE_H
#define FLATCOLORGEOMETRYNODE_H

#include <QSGFlatColorMaterial>
#include <QSGGeometryNode>

namespace debugger
{
class FlatColorGeometryNode : public QSGGeometryNode
{
public:
    struct Style
    {
        QColor color = Qt::GlobalColor::darkGreen;
        QSGGeometry::DrawingMode mode = QSGGeometry::DrawingMode::DrawLineStrip;
        float width = 1.0f;
    };

public:
    FlatColorGeometryNode(bool useUInt32Index = false);

    QColor const &color() const;
    void setColor(QColor const &color);

    bool isVisible() const;
    void setIsVisible(bool isVisible);

    bool isSubtreeBlocked() const override;

protected:
    QSGGeometry qsg_geometry_;
    QSGFlatColorMaterial material_;
    bool visible_;
    Style style_;
};
} // namespace debugger
#endif // FLATCOLORGEOMETRYNODE_H
