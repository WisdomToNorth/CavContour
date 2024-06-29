#include "PlineGraphicItem.h"

#include <iostream>

#include "viewer/graphicshelpers.h"
#include "viewer/segmentnode.h"
#include "viewer/simplecirclenode.h"

namespace debugger
{
PlineGraphicItem::PlineGraphicItem()
{
    this->setOpacity(1.0);
    drawstyle_ = DrawStyle();
}

void PlineGraphicItem::addSegment(const Segment &seg)
{
    SegmentNode *newseg = new SegmentNode(drawstyle_);
    appendChildNode(newseg);
    newseg->setFlag(QSGNode::OwnedByParent);
    newseg->setData(seg);
    newseg->update();
}

void PlineGraphicItem::addPoint(qreal x, qreal y)
{
    const qreal pointRadius = 0.05;
    auto newNode = new SimpleCircleNode(drawstyle_);
    appendChildNode(newNode);
    newNode->setFlag(QSGNode::OwnedByParent);
    newNode->setGeometry(x, y, pointRadius);
    newNode->update();
}

void PlineGraphicItem::update()
{
    for (const Segment &seg : pline_)
    {
        if (draw_vertex_)
        {
            addPoint(seg.x0, seg.y0);
        }
        addSegment(seg);
    }

    if (pline_.size() > 0)
    {
        if (draw_vertex_)
        {
            addPoint(pline_.back().x1, pline_.back().y1);
        }
    }
}

void PlineGraphicItem::setData(const Pline &pline)
{
    clear();
    pline_ = pline;
}

DrawStyle PlineGraphicItem::drawStyle() const
{
    return drawstyle_;
}

void PlineGraphicItem::setDrawStyle(const DrawStyle &drawstyle)
{
    if (drawstyle_ == drawstyle)
    {
        return;
    }

    QSGNode *node = firstChild();
    while (node)
    {
        auto circle = static_cast<SimpleCircleNode *>(node);
        circle->updateDrawStyle(drawstyle);
        node = node->nextSibling();
    }
}

void PlineGraphicItem::setVisible(bool visible)
{
    visible_ = visible;
    this->setOpacity(visible ? 1.0 : 0.0);
    // TODO: may set all sub nodes visible
}

void PlineGraphicItem::clear()
{
    removeAllChildNodes();
}
} // namespace debugger
