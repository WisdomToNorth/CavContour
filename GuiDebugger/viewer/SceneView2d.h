#ifndef PLINEOFFSETVIEW_H
#define PLINEOFFSETVIEW_H

#include <unordered_set>
#include <vector>

#include <QMatrix4x4>
#include <QQuickItem>
#include <QSGOpacityNode>

#include "CaseCreator.h"

class QSGOpacityNode;
namespace debugger
{
class PlineGraphicItem;
class SceneViewer : public QQuickItem
{
    Q_OBJECT

public:
    explicit SceneViewer(QQuickItem *parent = nullptr);

    void setUiScaleFactor(double scale_factor);

protected:
    QSGNode *updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

#if (QT_VERSION >= QT_VERSION_CHECK(5, 6, 0) && QT_VERSION < QT_VERSION_CHECK(6, 1, 0))
    void geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry) override;
#elif (QT_VERSION >= QT_VERSION_CHECK(6, 1, 0))
    void geometryChange(const QRectF &newGeometry, const QRectF &oldGeometry) override;
#endif

private:
    void updateCoordMatrices(qreal width, qreal height);
    QPoint getMouseEventGlobalPoint(QMouseEvent *event);
    QPointF convertToGlobalUICoord(const QPointF &pt);
    QPointF convertFromGlobalUICoord(const QPointF &pt);

private:
    double ui_scale_factor_ = 100;
    QMatrix4x4 real_to_ui_coord_;
    QMatrix4x4 ui_to_real_coord_;
    double pick_tol_ = 0.05;
    std::unordered_set<PlineGraphicItem *> added_;
    /*Action flag*/
    bool editing_vertex_ = false;
};
} // namespace debugger
#endif
