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
    setAcceptHoverEvents(true);

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
    if (caseIndex() == caseindex)
    {
        return;
    }
    std::cout << "SceneViewer::setCaseIndex: " << caseindex.toStdString() << std::endl;
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
    {
        return;
    }
    std::cout << "SceneViewer::setShowVertexes: " << show_vertex << std::endl;
    show_vertex_ = show_vertex;
    update();
    emit showVertexChangedSig(show_vertex_);
}

void SceneViewer::setEnableSlide(bool enable_slide)
{
    if (enable_slide_ == enable_slide)
    {
        return;
    }
    std::cout << "SceneViewer::setEnableSlide: " << enable_slide << std::endl;
    enable_slide_ = enable_slide;
    emit enableSlideChangedSig(enable_slide_);
}

bool SceneViewer::enableSlide() const
{
    return enable_slide_;
}

void SceneViewer::setShowAxis(bool show_axis)
{
    if (show_axis_ == show_axis)
    {
        return;
    }
    std::cout << "SceneViewer::setShowAxis: " << show_axis << std::endl;
    show_axis_ = show_axis;
    emit showAxisChangedSig(show_axis_);
    update();
}

bool SceneViewer::showAxis() const
{
    return show_axis_;
}

void SceneViewer::setShowDir(bool show_dir)
{
    if (show_dir_ == show_dir)
        return;

    std::cout << "SceneViewer::setShowDir: " << show_dir << std::endl;
    show_dir_ = show_dir;
    emit showDirChangedSig(show_dir_);
    update();
}

bool SceneViewer::showDir() const
{
    return show_dir_;
}

void SceneViewer::loadCase(QString caseindex)
{
    std::cout << "SceneViewer::loadCase: " << caseindex.toStdString() << std::endl;
}
void SceneViewer::saveCase(QString caseindex)
{
    std::cout << "SceneViewer::saveCase: " << caseindex.toStdString() << std::endl;
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
        const auto &pick_res = doc->hitTest(pick.x(), pick.y(), Settings::instance().pickTol());
        if (pick_res.size() > 0)
        {
            doc->setEditing(pick_res);
            editing_vertex_ = true;
            event->accept();
            return;
        }
    }
    event->ignore();
}

void SceneViewer::mouseMoveEvent(QMouseEvent *event)
{
    if (editing_vertex_)
    {
        QPointF cur_mouse = getMouseEventGlobalPoint(event);
        QPointF cur_pick = convertFromGlobalUICoord(cur_mouse);
        if (DocData *doc = DocManager::instance().getCurDoc(); doc)
        {
            doc->editData(cur_pick.x(), cur_pick.y(), Settings::instance().pickTol());
            update();

            QString location = getLocLabel(cur_pick, Settings::instance().showPrecision());
            emit mouseLocationChanged(location);
            return;
        }
    }

    event->ignore();
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
            return;
        }
    }

    event->ignore();
}

void SceneViewer::hoverMoveEvent(QHoverEvent *event)
{
    QPointF mouse_pick_pt = getMouseEventGlobalPoint(event);
    QPointF pick = convertFromGlobalUICoord(mouse_pick_pt);
    QString location = getLocLabel(pick, Settings::instance().showPrecision());
    emit mouseLocationChanged(location);
}

QString SceneViewer::getLocLabel(const QPointF &pt, int precision)
{
    // 假设最大整数部分宽度为6，加上小数点和可能的负号
    int totalWidth = 6 + 1 + precision;

    QString xStr = QString("%1").arg(pt.x(), totalWidth, 'f', precision, ' ');
    QString yStr = QString("%1").arg(pt.y(), totalWidth, 'f', precision, ' ');

    return QString("X: %1, Y: %2").arg(xStr).arg(yStr);
}

void SceneViewer::updateCoordMatrices(qreal width, qreal height)
{
    real_to_ui_coord_.setToIdentity();
    real_to_ui_coord_.translate(static_cast<float>(width / 2), static_cast<float>(height / 2));
    real_to_ui_coord_.scale(Settings::instance().uiScaleFactor(),
                            -Settings::instance().uiScaleFactor());
    ui_to_real_coord_ = real_to_ui_coord_.inverted();
}

QString SceneViewer::mouseLoc() const
{
    return getLocLabel(QPointF(0, 0), Settings::instance().showPrecision());
}

QPointF SceneViewer::convertToGlobalUICoord(const QPointF &pt)
{
    return mapToGlobal(real_to_ui_coord_.map(pt));
}

QPointF SceneViewer::convertFromGlobalUICoord(const QPointF &pt)
{
    return ui_to_real_coord_.map(mapFromGlobal(pt));
}

#if (QT_VERSION >= QT_VERSION_CHECK(6, 1, 0))
QPointF SceneViewer::getMouseEventGlobalPoint(QSinglePointEvent *event)
{
    return event->globalPosition();
}
void SceneViewer::geometryChange(const QRectF &newGeometry, const QRectF &oldGeometry)
{
    QQuickItem::geometryChange(newGeometry, oldGeometry);
    Q_UNUSED(oldGeometry)

    updateCoordMatrices(newGeometry.width(), newGeometry.height());
    update();
}

#elif (QT_VERSION >= QT_VERSION_CHECK(5, 6, 0) && QT_VERSION < QT_VERSION_CHECK(6, 1, 0))
void SceneViewer::geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry)
{
    QQuickItem::geometryChanged(newGeometry, oldGeometry);
    Q_UNUSED(oldGeometry)

    updateCoordMatrices(newGeometry.width(), newGeometry.height());
    update();
}

QPointF SceneViewer::getMouseEventGlobalPoint(QMouseEvent *event)
{
    return event->globalPos();
}
QPointF SceneViewer::getMouseEventGlobalPoint(QHoverEvent *event)
{
    QPointF cur_pos = event->posF();
    return mapToGlobal(cur_pos);
}
#endif
} // namespace debugger
