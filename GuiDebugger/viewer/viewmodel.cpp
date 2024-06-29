#include "viewmodel.h"

#include <QDebug>

#include "viewer/flatcolorgeometrynode.h"
#include "viewer/graphicshelpers.h"

namespace debugger
{

NgViewModel::NgViewModel()
{
}
NgViewModel::NgViewModel(const ViewData &viewdata)
{
    setData(viewdata);
}

NgViewModel::~NgViewModel()
{
}

void NgViewModel::clearData()
{
    for (auto &pline : pline_nodes_)
    {
        delete pline;
    }
    pline_nodes_.clear();
}

void NgViewModel::update()
{
    for (PlineGraphicItem *node : pline_nodes_)
    {
        node->update();
    }
}

void NgViewModel::setData(const ViewData &viewdata)
{
    clearData();
    for (const auto &pline : viewdata)
    {
        auto node = new PlineGraphicItem();
        node->setData(pline);
        node->setVisible(true);
        pline_nodes_.emplace_back(node);
    }
}

void NgViewModel::setVisible(bool isVisible)
{
    for (auto &pline : pline_nodes_)
    {
        pline->setVisible(isVisible);
    }
}

bool NgViewModel::isVisible() const
{
    for (const auto &pline : pline_nodes_)
    {
        if (pline->isVisible())
        {
            return true;
        }
    }
    return false;
}

void NgViewModel::setDrawStyle(const DrawStyle &drawstyle)
{
    for (auto &pline : pline_nodes_)
    {
        pline->setDrawStyle(drawstyle);
    }
}

} // namespace debugger
