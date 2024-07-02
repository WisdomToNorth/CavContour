#ifndef DEBUGGER_VIEWER_H
#define DEBUGGER_VIEWER_H

#include <unordered_set>
#include <vector>

#include <QMatrix4x4>
#include <QQuickItem>
#include <QString>
#include <QStringList>

namespace debugger
{
class PlineGraphicItem;
class SceneViewer : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(bool showVertex READ showVertex WRITE setShowVertexes NOTIFY showVertexChangedSig)
    Q_PROPERTY(QString caseIndex READ caseIndex WRITE setCaseIndex NOTIFY caseIndexChangedSig)
    Q_PROPERTY(QStringList caseList READ caseList CONSTANT)
    Q_PROPERTY(QString mouseLoc READ mouseLoc NOTIFY mouseLocationChanged)

public:
    explicit SceneViewer(QQuickItem *parent = nullptr);

    bool showVertex() const;
    void setShowVertexes(bool show_vertex);

    QString caseIndex() const;
    void setCaseIndex(QString caseindex);

    QStringList caseList() const;
    QString mouseLoc() const;

signals:
    void showVertexChangedSig(bool showVertex);
    void caseIndexChangedSig(QString caseindex);
    void mouseLocationChanged(QString location);

protected:
    QSGNode *updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void hoverMoveEvent(QHoverEvent *event) override;

#if (QT_VERSION >= QT_VERSION_CHECK(5, 6, 0) && QT_VERSION < QT_VERSION_CHECK(6, 1, 0))
    void geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry) override;
    QPointF getMouseEventGlobalPoint(QMouseEvent *event);
    QPointF getMouseEventGlobalPoint(QHoverEvent *event);
#elif (QT_VERSION >= QT_VERSION_CHECK(6, 1, 0))
    void geometryChange(const QRectF &newGeometry, const QRectF &oldGeometry) override;
    QPointF getMouseEventGlobalPoint(QSinglePointEvent *event);
#endif

private:
    void updateCoordMatrices(qreal width, qreal height);
    QPointF convertToGlobalUICoord(const QPointF &pt);
    QPointF convertFromGlobalUICoord(const QPointF &pt);
    static QString getLocLabel(const QPointF &pt, int precision);

private:
    /*change by UI*/
    bool show_vertex_ = true;
    bool enable_slide_ = true;

private:
    /*change by manual*/
    const double ui_scale_factor_ = 50;
    const double pick_tol_ = 0.1;
    const int show_precision_ = 3;

private:
    /*app run data*/
    std::unordered_set<PlineGraphicItem *> added_;
    QMatrix4x4 real_to_ui_coord_;
    QMatrix4x4 ui_to_real_coord_;
    bool editing_vertex_ = false;
};
} // namespace debugger
#endif
