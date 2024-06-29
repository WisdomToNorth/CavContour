#ifndef GEOCANVASHELPER_H
#define GEOCANVASHELPER_H

#include <QMatrix4x4>
#include <QQuickItem>

namespace debugger
{
class GeoCanvasHelper : public QQuickItem
{
    Q_OBJECT
public:
    explicit GeoCanvasHelper(QQuickItem *parent = nullptr);
    QPointF convertToGlobalUICoord(const QPointF &pt);
    QPointF convertFromGlobalUICoord(const QPointF &pt);

protected:
    double ui_scale_factor_;
    QMatrix4x4 real_to_ui_coord_;
    QMatrix4x4 ui_to_real_coord_;

protected:
    void updateCoordMatrices(qreal width, qreal height);

#if (QT_VERSION >= QT_VERSION_CHECK(5, 6, 0) && QT_VERSION < QT_VERSION_CHECK(6, 1, 0))
    void geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry) override;
#elif (QT_VERSION >= QT_VERSION_CHECK(6, 1, 0))
    void geometryChange(const QRectF &newGeometry, const QRectF &oldGeometry) override;
#endif
};
} // namespace debugger
#endif // GEOMETRYCANVASITEM_H
