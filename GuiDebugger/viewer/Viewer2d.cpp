#include "viewer/Viewer2d.h"

#include <iostream>

#include <QSGTransformNode>

#include <cavc/polylineoffsetislands.hpp>

#include "viewer/caseviewmodel.h"
#include "viewer/simplecirclenode.h"

#include "CaseCreator.h"
#include "DocManager.h"
#include "settings/settings.h"

using namespace cavc;
namespace debugger
{
SceneViewer::SceneViewer(QQuickItem *parent)
    : QQuickItem(parent)
{
    setFlag(ItemHasContents, true);
    setAcceptedMouseButtons(Qt::AllButtons);

    updateCoordMatrices(width(), height());
    DocManager::instance().setCurDoc("case9");
}

QStringList SceneViewer::caseList() const
{
    QStringList case_list;
    for (const std::string &name : CaseCreator::getCaseNames())
    {
        case_list.append(QString::fromStdString(name));
    }

    return case_list;
}

QString SceneViewer::caseIndex() const
{
    return "TODO";
}

void SceneViewer::setCaseIndex(QString caseindex)
{
    emit caseIndexChangedSig(caseindex);
    update();
}

bool SceneViewer::showVertex() const
{
    return show_vertex_;
}

void SceneViewer::setShowVertexes(bool show_vertex)
{
    if (show_vertex_ == show_vertex)
        return;

    show_vertex_ = show_vertex;
    update();
    emit showVertexChangedSig(show_vertex_);
}

QSGNode *SceneViewer::updatePaintNode(QSGNode *old_node, QQuickItem::UpdatePaintNodeData *)
{
    QSGTransformNode *root_node =
        !old_node ? new QSGTransformNode() : static_cast<QSGTransformNode *>(old_node);
    root_node->setMatrix(real_to_ui_coord_);

    if (DocData *cur_doc = DocManager::instance().getCurDoc(); cur_doc)
    {
        CaseViewModel *case_vm_ = cur_doc->getVMData();
        const std::vector<PlineGraphicItem *> &pline_nodes = case_vm_->getPlineNodes();
        for (PlineGraphicItem *node : pline_nodes)
        {
            if (added_.find(node) != added_.end())
            {
                continue;
            }
            root_node->appendChildNode(node);
            added_.insert(node);
            std::cout << "Add new item: " << added_.size() << std::endl;
        }
    }

    return root_node;

    //// clear old nodes
    // auto oldChild = root_node->firstChild();
    // while (oldChild)
    // {
    //     auto next = oldChild->nextSibling();
    //     root_node->removeChildNode(oldChild);
    //     delete oldChild;
    //     oldChild = next;
    // }
}

void SceneViewer::mousePressEvent(QMouseEvent *event)
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

void SceneViewer::mouseMoveEvent(QMouseEvent *event)
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

void SceneViewer::mouseReleaseEvent(QMouseEvent *event)
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

void SceneViewer::setUiScaleFactor(double scale_factor)
{
    ui_scale_factor_ = scale_factor;
    updateCoordMatrices(width(), height());
    update();
}

void SceneViewer::updateCoordMatrices(qreal width, qreal height)
{
    real_to_ui_coord_.setToIdentity();
    real_to_ui_coord_.translate(static_cast<float>(width / 2), static_cast<float>(height / 2));
    real_to_ui_coord_.scale(static_cast<float>(ui_scale_factor_),
                            static_cast<float>(-ui_scale_factor_));
    ui_to_real_coord_ = real_to_ui_coord_.inverted();
}

QPoint SceneViewer::getMouseEventGlobalPoint(QMouseEvent *event)
{
#if (QT_VERSION >= QT_VERSION_CHECK(6, 0, 0))
    QPointF startPos = event->globalPosition();
#else
    QPointF startPos = event->globalPos();
#endif
    return QPoint(int(startPos.x()), int(startPos.y()));
}

#if (QT_VERSION >= QT_VERSION_CHECK(5, 6, 0) && QT_VERSION < QT_VERSION_CHECK(6, 1, 0))
void SceneViewer::geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry)
{
    QQuickItem::geometryChanged(newGeometry, oldGeometry);
#elif (QT_VERSION >= QT_VERSION_CHECK(6, 1, 0))
void SceneViewer::geometryChange(const QRectF &newGeometry, const QRectF &oldGeometry)
{
    QQuickItem::geometryChange(newGeometry, oldGeometry);
#endif
    Q_UNUSED(oldGeometry)

    updateCoordMatrices(newGeometry.width(), newGeometry.height());
    update();
}

QPointF SceneViewer::convertToGlobalUICoord(const QPointF &pt)
{
    return mapToGlobal(real_to_ui_coord_.map(pt));
}

QPointF SceneViewer::convertFromGlobalUICoord(const QPointF &pt)
{
    return ui_to_real_coord_.map(mapFromGlobal(pt));
}
} // namespace debugger
