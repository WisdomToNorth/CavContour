#include "offsetisland/plineoffsetislandsalgorithmview.h"

#include <iostream>

#include <QSGTransformNode>

#include <cavc/polylineoffsetislands.hpp>

#include "viewer/simplecirclenode.h"
#include "viewer/viewmodel.h"

#include "datamanager.h"
#include "settings/settings.h"

using namespace cavc;
namespace debugger
{
OffsetIslandsView::OffsetIslandsView(QQuickItem *parent)
    : GeoCanvasHelper(parent)
    , m_showVertexes(true)
    , m_offsetDelta(1)
    , m_offsetCount(20)
    , m_vertexGrabbed(std::numeric_limits<std::size_t>::max())
{
    auto &docData = DocumetData::getInstance();
    docData.changeData("default1");

    auto machine_type = NgSettings::AppAlgorithmCore();
    std::cout << "type in offset class: " << static_cast<int>(machine_type) << std::endl;
    switch (machine_type)
    {
    case NgSettings::AppAlgorithmCore::kCavc:
    {
        DataUtils::buildCase0(case_vm_);
        break;
    }
    case NgSettings::AppAlgorithmCore::kNGPoly: break;
    case NgSettings::AppAlgorithmCore::kClipper: break;

    default: break;
    }
}

QString OffsetIslandsView::caseIndex() const
{
    return DocumetData::getInstance().case_index_;
}

void OffsetIslandsView::setCaseIndex(QString caseindex)
{
    std::cout << "caseindex: " << caseindex.toStdString() << std::endl;
    if (caseindex == DocumetData::getInstance().case_index_)
    {
        return;
    }
    std::cout << "change case data" << std::endl;

    DocumetData::getInstance().changeData(caseindex);
    CavcPolygonSet cavc_polygonset;
    DataUtils::buildCavcCase(DocumetData::getInstance().case_data_, cavc_polygonset);

    emit changeCaseDataSignal(caseindex);
    update();
}

bool OffsetIslandsView::showVertexes() const
{
    return m_showVertexes;
}

void OffsetIslandsView::setShowVertexes(bool showVertexes)
{
    if (m_showVertexes == showVertexes)
        return;

    m_showVertexes = showVertexes;
    update();
    emit showVertexesChanged(m_showVertexes);
}

double OffsetIslandsView::offsetDelta() const
{
    return m_offsetDelta;
}

void OffsetIslandsView::setOffsetDelta(double offsetDelta)
{
    if (qFuzzyCompare(m_offsetDelta, offsetDelta))
    {
        return;
    }

    m_offsetDelta = offsetDelta;
    update();
    emit offsetDeltaChanged(m_offsetDelta);
}

int OffsetIslandsView::offsetCount() const
{
    return m_offsetCount;
}

void OffsetIslandsView::setOffsetCount(int offsetCount)
{
    if (m_offsetCount == offsetCount)
        return;

    m_offsetCount = offsetCount;
    update();
    emit offsetCountChanged(m_offsetCount);
}

QSGNode *OffsetIslandsView::updatePaintNode(QSGNode *oldNode, QQuickItem::UpdatePaintNodeData *)
{
    QSGTransformNode *rootNode = nullptr;
    if (!oldNode)
    {
        rootNode = new QSGTransformNode();
    }
    else
    {
        rootNode = static_cast<QSGTransformNode *>(oldNode);
    }
    rootNode->setMatrix(real_to_ui_coord_);

    for (auto &vm : case_vm_)
    {
        std::vector<PlineGraphicItem *> pline_nodes = vm->getNodes();
        for (auto &node : pline_nodes)
        {
            rootNode->appendChildNode(node);
            node->update();
        }
    }

    return rootNode;
}

void OffsetIslandsView::mousePressEvent(QMouseEvent *event)
{
    mouse_pick_pt_ = QPointF(event->globalX(), event->globalY());

    auto &case_data = DocumetData::getInstance().case_data_;

    // find if pick to point in case_data_, record to vertex_pick_index_. if not find, put {-1, -1}
    for (int i = 0; i < case_data.size(); i++)
    {
        auto const &data = case_data[i].first;
        for (int j = 0; j < data.size(); j++)
        {
            QPointF vPosInGlobal =
                convertToGlobalUICoord(QPointF(std::get<0>(data[j]), std::get<1>(data[j])));
            if (utils::fuzzyEqual(vPosInGlobal.x(), mouse_pick_pt_.x(), 5.0) &&
                utils::fuzzyEqual(vPosInGlobal.y(), mouse_pick_pt_.y(), 5.0))
            {
                vertex_pick_index_ = std::make_pair(i, j);
                break;
            }
        }
    }

    if (!isVertexGrabbed())
    {
        event->ignore();
        return;
    }

    event->accept();
}

void OffsetIslandsView::mouseMoveEvent(QMouseEvent *event)
{
    if (!isVertexGrabbed())
    {
        return;
    }

    // convert back from global coordinates to get real delta
    QPointF newGlobalVertexPos = QPointF(event->globalX(), event->globalY());
    QPointF newLocalVertexPos = mapFromGlobal(newGlobalVertexPos);
    QPointF newRealVertexPos = ui_to_real_coord_ * newLocalVertexPos;

    int pline_index = vertex_pick_index_.first;
    int vertex_index = vertex_pick_index_.second;
    auto &case_changed = DocumetData::getInstance().case_data_[pline_index].first[vertex_index];

    std::get<0>(case_changed) = newRealVertexPos.x();
    std::get<1>(case_changed) = newRealVertexPos.y();

    switch (NgSettings::AppAlgorithmCore())
    {
    case NgSettings::AppAlgorithmCore::kCavc:
    {
        // ////way 1:  regenerate cavc data
        // IsHole is_hole = DocumetData::getInstance().case_data_[pline_index].second;
        // cavc_polygonset_[pline_index] = {
        //     DataUtils::buildCavcPline(DocumetData::getInstance().case_data_[pline_index].first,
        //                               is_hole),
        //     is_hole};

        // ////way 2:  update polyline, more efficient, not able to work well if index is 0 or n-1
        // // auto &vertex = cavc_polygonset_[pline_index].first[vertex_index];
        // // vertex.x() = newRealVertexPos.x();
        // // vertex.y() = newRealVertexPos.y();
        break;
    }
    case NgSettings::AppAlgorithmCore::kNGPoly: break;
    case NgSettings::AppAlgorithmCore::kClipper: break;

    default: break;
    }

    update();
}

void OffsetIslandsView::mouseReleaseEvent(QMouseEvent *event)
{
    if (!isVertexGrabbed())
    {
        return;
    }
    else
    {
        m_vertexGrabbed = std::numeric_limits<std::size_t>::max();
        event->accept();
        resetVertexGrabbed();
    }
}

bool OffsetIslandsView::isVertexGrabbed()
{
    return vertex_pick_index_.first != -1 && vertex_pick_index_.second != -1;
}

void OffsetIslandsView::resetVertexGrabbed()
{
    vertex_pick_index_ = std::make_pair(-1, -1);
}

} // namespace debugger
