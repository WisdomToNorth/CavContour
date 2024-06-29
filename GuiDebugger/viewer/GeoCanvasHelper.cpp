#include "GeoCanvasHelper.h"

namespace debugger
{

GeoCanvasHelper::GeoCanvasHelper(QQuickItem *parent)
    : QQuickItem(parent)
    , ui_scale_factor_(20)
{
    setFlag(ItemHasContents, true);
    setAcceptedMouseButtons(Qt::LeftButton);
    updateCoordMatrices(width(), height());
}

void GeoCanvasHelper::updateCoordMatrices(qreal width, qreal height)
{
    real_to_ui_coord_.setToIdentity();
    real_to_ui_coord_.translate(static_cast<float>(width / 2), static_cast<float>(height / 2));
    real_to_ui_coord_.scale(static_cast<float>(ui_scale_factor_),
                            static_cast<float>(-ui_scale_factor_));
    ui_to_real_coord_ = real_to_ui_coord_.inverted();
}

#if (QT_VERSION >= QT_VERSION_CHECK(5, 6, 0) && QT_VERSION < QT_VERSION_CHECK(6, 1, 0))
void GeoCanvasHelper::geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry)
{
    QQuickItem::geometryChanged(newGeometry, oldGeometry);
#elif (QT_VERSION >= QT_VERSION_CHECK(6, 1, 0))
void GeoCanvasHelper::geometryChange(const QRectF &newGeometry, const QRectF &oldGeometry)
{
    QQuickItem::geometryChange(newGeometry, oldGeometry);
#endif
    Q_UNUSED(oldGeometry)

    updateCoordMatrices(newGeometry.width(), newGeometry.height());
    update();
}

QPointF GeoCanvasHelper::convertToGlobalUICoord(const QPointF &pt)
{
    return mapToGlobal(real_to_ui_coord_.map(pt));
}

QPointF GeoCanvasHelper::convertFromGlobalUICoord(const QPointF &pt)
{
    return ui_to_real_coord_.map(mapFromGlobal(pt));
}
} // namespace debugger
