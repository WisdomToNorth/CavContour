#include "PlineGraphicItem.h"

#include <cassert>
#include <iostream>

namespace debugger
{
PlineGraphicItem::PlineGraphicItem()
    : QSGOpacityNode()
{
    this->setOpacity(1.0);
    drawstyle_ = DrawStyle();
}

SegmentNode *PlineGraphicItem::createSegment(const RecordF &seg)
{
    SegmentNode *newseg = new SegmentNode(drawstyle_);
    appendChildNode(newseg);
    newseg->setFlag(QSGNode::OwnedByParent);
    newseg->setData(seg);
    newseg->update();
    return newseg;
}

SimpleCircleNode *PlineGraphicItem::createPoint(qreal x, qreal y)
{
    const qreal pointRadius = 0.05;
    SimpleCircleNode *newNode = new SimpleCircleNode(drawstyle_);
    appendChildNode(newNode);
    newNode->setFlag(QSGNode::OwnedByParent);
    newNode->setGeometry(x, y, pointRadius);
    newNode->update();
    return newNode;
}
void PlineGraphicItem::updateNode(size_t index, const RecordF &seg)
{
    if (index < segments_.size())
    {
        segments_[index]->setData(seg);
        segments_[index]->update();
        circles_[index]->setGeometry(seg.x0, seg.y0, 0.05);
        circles_[index]->update();
    }
}

void PlineGraphicItem::updateData(const Pline &pline)
{
    if (draw_vertex_ && (circles_.size() > 0))
    {
        assert(circles_.size() == segments_.size());
    }

    if (segments_.size() < pline.size())
    {
        for (size_t i = segments_.size(); i < pline.size(); i++)
        {
            segments_.emplace_back(createSegment(pline[i]));
            circles_.emplace_back(createPoint(pline[i].x0, pline[i].y0));
        }
    }
    else if (segments_.size() > pline.size())
    {
        for (size_t i = segments_.size(); i > pline.size(); i--)
        {
            delete segments_[i - 1];
            segments_.pop_back();
            delete circles_[i - 1];
            circles_.pop_back();
        }
    }

    for (size_t i = 0; i < pline.size(); i++)
    {
        segments_[i]->setData(pline[i]);
        segments_[i]->update();
        circles_[i]->setGeometry(pline[i].x0, pline[i].y0, 0.05);
        circles_[i]->update();
    }
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
}

void PlineGraphicItem::clear()
{
    removeAllChildNodes();
}
} // namespace debugger
