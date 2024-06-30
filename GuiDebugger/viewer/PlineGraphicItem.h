#ifndef PLINEGRAPHICITEM_H
#define PLINEGRAPHICITEM_H
#include <QSGOpacityNode>

#include "viewer/segmentnode.h"
#include "viewer/simplecirclenode.h"

#include "drawstyle.h"
#include "vmparameter.h"

namespace debugger
{
class PlineGraphicItem : public QSGOpacityNode
{
public:
    PlineGraphicItem();

    void updateData(const Pline &pline);
    void updateNode(size_t index, const RecordF &seg);

    DrawStyle drawStyle() const;
    void setDrawStyle(const DrawStyle &drawstyle);

    void setDrawVertex(bool draw_vertex)
    {
        draw_vertex_ = draw_vertex;
    }
    bool drawVertex() const
    {
        return draw_vertex_;
    }
    void setVisible(bool visible);
    bool isVisible() const
    {
        return visible_;
    }

private:
    SimpleCircleNode *createPoint(qreal x, qreal y);
    SegmentNode *createSegment(const RecordF &seg);

    void clear();

private:
    std::vector<SegmentNode *> segments_;
    std::vector<SimpleCircleNode *> circles_;

    DrawStyle drawstyle_;
    bool draw_vertex_ = true;
    bool visible_ = true;
};
} // namespace debugger
#endif
