#ifndef AXISGRAPHICITEM_H
#define AXISGRAPHICITEM_H
#include <QSGOpacityNode>

#include "GeoNode.h"
#include "drawstyle.h"

namespace debugger
{
class AxisGraphicItem : public QSGOpacityNode
{
public:
    AxisGraphicItem();

    void setVisible(bool visible)
    {
        visible_ = visible;
    }
    bool isVisible() const
    {
        return visible_;
    }
    bool drawSubLines() const
    {
        return draw_sub_lines_;
    }
    void setDrawSubLines(bool draw_sub_lines)
    {
        draw_sub_lines_ = draw_sub_lines;
    }
    bool drawAxis() const
    {
        return draw_axis_;
    }
    void setDrawAxis(bool draw_axis)
    {
        draw_axis_ = draw_axis;
    }

private:
    bool visible_ = true;
    bool draw_sub_lines_ = true;
    bool draw_axis_ = true;
};
} // namespace debugger
#endif
