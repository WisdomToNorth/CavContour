#include "offsetisland/offsetview.h"

#include <iostream>

#include <QSGTransformNode>

#include <cavc/polylineoffsetislands.hpp>

#include "viewer/caseviewmodel.h"
#include "viewer/simplecirclenode.h"

#include "DocManager.h"
#include "settings/settings.h"

using namespace cavc;
namespace debugger
{
OffsetView::OffsetView(QQuickItem *parent)
    : QQuickItem(parent)
    , m_showVertexes(true)
    , m_offsetDelta(1)
    , m_offsetCount(20)
{
    setFlag(ItemHasContents, true);
    setAcceptedMouseButtons(Qt::AllButtons);

    updateCoordMatrices(width(), height());
    DocManager::instance().setCurDoc("case0");
}

QString OffsetView::caseIndex() const
{
    return "TODO";
}

void OffsetView::setCaseIndex(QString caseindex)
{
    emit changeCaseDataSignal(caseindex);
    update();
}

bool OffsetView::showVertexes() const
{
    return m_showVertexes;
}

void OffsetView::setShowVertexes(bool showVertexes)
{
    if (m_showVertexes == showVertexes)
        return;

    m_showVertexes = showVertexes;
    update();
    emit showVertexesChanged(m_showVertexes);
}

double OffsetView::offsetDelta() const
{
    return m_offsetDelta;
}

void OffsetView::setOffsetDelta(double offsetDelta)
{
    if (qFuzzyCompare(m_offsetDelta, offsetDelta))
    {
        return;
    }

    m_offsetDelta = offsetDelta;
    update();
    emit offsetDeltaChanged(m_offsetDelta);
}

int OffsetView::offsetCount() const
{
    return m_offsetCount;
}

void OffsetView::setOffsetCount(int offsetCount)
{
    if (m_offsetCount == offsetCount)
        return;

    m_offsetCount = offsetCount;
    update();
    emit offsetCountChanged(m_offsetCount);
}

QSGNode *OffsetView::updatePaintNode(QSGNode *oldNode, QQuickItem::UpdatePaintNodeData *)
{
    QSGTransformNode *rootNode = nullptr;
    if (!oldNode)
    {
        rootNode = new QSGTransformNode();
    }
    else
    {
        rootNode = static_cast<QSGTransformNode *>(oldNode);
        // clear old nodes
        // auto oldChild = dyn_parent_node_->firstChild();
        // while (oldChild)
        // {
        //     auto next = oldChild->nextSibling();
        //     dyn_parent_node_->removeChildNode(oldChild);
        //     delete oldChild;
        //     oldChild = next;
        // }
    }

    rootNode->setMatrix(real_to_ui_coord_);
    DocData *cur_doc = DocManager::instance().getCurDoc();
    if (cur_doc)
    {
        CaseViewModel *case_vm_ = cur_doc->getVMData();
        const std::vector<PlineGraphicItem *> &pline_nodes = case_vm_->getPlineNodes();
        for (PlineGraphicItem *node : pline_nodes)
        {
            if (added_.find(node) != added_.end())
            {
                continue;
            }
            rootNode->appendChildNode(node);
            added_.insert(node);
        }
    }

    return rootNode;
}

void OffsetView::mousePressEvent(QMouseEvent *event)
{
    if (DocData *doc = DocManager::instance().getCurDoc(); doc)
    {
        QPointF mouse_pick_pt = getMouseEventGlobalPoint(event);
        QPointF pick = convertFromGlobalUICoord(mouse_pick_pt);
        const auto &pick_res = doc->hitTest(pick.x(), pick.y(), pick_tol_);
        if (pick_res.size() > 0)
        {
            doc->setEditing(pick_res);
            editing_vertex_ = true;
            event->accept();
        }
    }
    else
    {
        QQuickItem::mousePressEvent(event);
    }
}

void OffsetView::mouseMoveEvent(QMouseEvent *event)
{
    if (editing_vertex_)
    {
        QPointF cur_mouse = getMouseEventGlobalPoint(event);
        QPointF cur_pick = convertFromGlobalUICoord(cur_mouse);
        if (DocData *doc = DocManager::instance().getCurDoc(); doc)
        {
            doc->editData(cur_pick.x(), cur_pick.y(), pick_tol_);
            update();
        }
    }
    else
    {
        QQuickItem::mouseMoveEvent(event);
    }
}

void OffsetView::mouseReleaseEvent(QMouseEvent *event)
{
    if (editing_vertex_)
    {
        editing_vertex_ = false;
        event->accept();
        if (DocData *doc = DocManager::instance().getCurDoc(); doc)
        {
            doc->resetEditing();
        }
    }
    QQuickItem::mouseReleaseEvent(event);
}

void OffsetView::setUiScaleFactor(double scale_factor)
{
    ui_scale_factor_ = scale_factor;
    updateCoordMatrices(width(), height());
    update();
}

void OffsetView::updateCoordMatrices(qreal width, qreal height)
{
    real_to_ui_coord_.setToIdentity();
    real_to_ui_coord_.translate(static_cast<float>(width / 2), static_cast<float>(height / 2));
    real_to_ui_coord_.scale(static_cast<float>(ui_scale_factor_),
                            static_cast<float>(-ui_scale_factor_));
    ui_to_real_coord_ = real_to_ui_coord_.inverted();
}

QPoint OffsetView::getMouseEventGlobalPoint(QMouseEvent *event)
{
#if (QT_VERSION >= QT_VERSION_CHECK(6, 0, 0))
    QPointF startPos = event->globalPosition();
#else
    QPointF startPos = event->globalPos();
#endif
    return QPoint(int(startPos.x()), int(startPos.y()));
}

#if (QT_VERSION >= QT_VERSION_CHECK(5, 6, 0) && QT_VERSION < QT_VERSION_CHECK(6, 1, 0))
void OffsetView::geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry)
{
    QQuickItem::geometryChanged(newGeometry, oldGeometry);
#elif (QT_VERSION >= QT_VERSION_CHECK(6, 1, 0))
void OffsetView::geometryChange(const QRectF &newGeometry, const QRectF &oldGeometry)
{
    QQuickItem::geometryChange(newGeometry, oldGeometry);
#endif
    Q_UNUSED(oldGeometry)

    updateCoordMatrices(newGeometry.width(), newGeometry.height());
    update();
}

QPointF OffsetView::convertToGlobalUICoord(const QPointF &pt)
{
    return mapToGlobal(real_to_ui_coord_.map(pt));
}

QPointF OffsetView::convertFromGlobalUICoord(const QPointF &pt)
{
    return ui_to_real_coord_.map(mapFromGlobal(pt));
}
} // namespace debugger
