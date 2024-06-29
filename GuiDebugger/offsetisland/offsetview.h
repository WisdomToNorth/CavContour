#ifndef PLINEOFFSETVIEW_H
#define PLINEOFFSETVIEW_H

#include <vector>

#include <cavc/polyline.hpp>

#include "viewer/GeoCanvasHelper.h"

#include "casedata.h"

class QSGOpacityNode;
namespace debugger
{
class OffsetView : public GeoCanvasHelper
{
    Q_OBJECT
    Q_PROPERTY(bool showVertexes READ showVertexes WRITE setShowVertexes NOTIFY showVertexesChanged)
    Q_PROPERTY(double offsetDelta READ offsetDelta WRITE setOffsetDelta NOTIFY offsetDeltaChanged)
    Q_PROPERTY(int offsetCount READ offsetCount WRITE setOffsetCount NOTIFY offsetCountChanged)
    Q_PROPERTY(QString caseIndex READ caseIndex WRITE setCaseIndex NOTIFY changeCaseDataSignal)

public:
    explicit OffsetView(QQuickItem *parent = nullptr);

    bool showVertexes() const;
    void setShowVertexes(bool showVertexes);

    double offsetDelta() const;
    void setOffsetDelta(double offsetDelta);

    int offsetCount() const;
    void setOffsetCount(int offsetCount);

    QString caseIndex() const;
    void setCaseIndex(QString caseindex);

signals:
    void showVertexesChanged(bool showVertexes);
    void offsetDeltaChanged(double offsetDelta);
    void offsetCountChanged(int offsetCount);
    void changeCaseDataSignal(QString caseindex);

protected:
    /*Cavc*/
    QSGNode *updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *) override;

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    std::vector<NgViewModel *> case_vm_;

    bool m_showVertexes;
    double m_offsetDelta;
    int m_offsetCount;

    bool isVertexGrabbed();
    void resetVertexGrabbed();

    QPointF mouse_pick_pt_;
    std::pair<int, int> vertex_pick_index_{-1, -1};

    std::size_t m_vertexGrabbed;
    QPointF m_origVertexGlobalPos;
};
} // namespace debugger
#endif // PLINEOFFSETISLANDSALGORITHMVIEW_H