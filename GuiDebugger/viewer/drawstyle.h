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
    double arcApproxError = 0.001;
    float width = 1.0f;
    bool visible = true;
    bool useUInt32Index = true;
    bool operator==(const DrawStyle &other) const;

    static QColor indexToColor(std::size_t index);
};

} // namespace debugger
#endif // DRAWSTYLE_H
