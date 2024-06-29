#ifndef DRAWSTYLE_H
#define DRAWSTYLE_H
#include <QColor>
#include <QSGGeometryNode>

namespace debugger
{
struct DrawStyle
{
    QColor color = Qt::GlobalColor::darkGreen;
    QSGGeometry::DrawingMode linetype = QSGGeometry::DrawingMode::DrawLineStrip;
    double arcApproxError = 0.005;
    float width = 2.0f;
    bool visible = true;
    bool useUInt32Index = true;
    bool operator==(const DrawStyle &other) const
    {
        return color == other.color && linetype == other.linetype &&
               arcApproxError == other.arcApproxError && width == other.width &&
               visible == other.visible && useUInt32Index == other.useUInt32Index;
    }
};

} // namespace debugger
#endif // DRAWSTYLE_H
