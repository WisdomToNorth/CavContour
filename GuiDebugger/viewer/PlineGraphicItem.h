#ifndef PLINEGRAPHICITEM_H
#define PLINEGRAPHICITEM_H
#include <QSGOpacityNode>

#include "drawstyle.h"
#include "vmparameter.h"

namespace debugger
{
class PlineGraphicItem : public QSGOpacityNode
{
public:
    PlineGraphicItem();
    void setData(const Pline &pline);
    void update();

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
    void addPoint(qreal x, qreal y);
    void addSegment(const Segment &seg);
    void clear();

private:
    Pline pline_;
    DrawStyle drawstyle_;
    bool draw_vertex_=true;
    bool visible_=true;
};
} // namespace debugger
#endif
