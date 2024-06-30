#include "caseviewmodel.h"

#include "viewer/GeoNode.h"

namespace debugger
{

CaseViewModel::CaseViewModel()
{
}
CaseViewModel::CaseViewModel(const ViewData &viewdata)
{
    updateData(viewdata);
}

CaseViewModel::~CaseViewModel()
{
    clearData();
}

void CaseViewModel::clearData()
{
    for (auto &pline : pline_nodes_)
    {
        delete pline;
    }
    pline_nodes_.clear();
}

void CaseViewModel::updateData(const ViewData &viewdata)
{
    if (viewdata.size() < pline_nodes_.size())
    {
        for (size_t i = viewdata.size(); i < pline_nodes_.size(); i++)
        {
            delete pline_nodes_[i];
        }
        pline_nodes_.resize(viewdata.size());
    }
    else if (viewdata.size() > pline_nodes_.size())
    {
        for (size_t i = pline_nodes_.size(); i < viewdata.size(); i++)
        {
            auto node = new PlineGraphicItem();
            node->setVisible(true);
            pline_nodes_.emplace_back(node);
        }
    }

    assert(pline_nodes_.size() == viewdata.size());
    for (size_t i = 0; i < pline_nodes_.size(); i++)
    {
        pline_nodes_[i]->updateData(viewdata[i]);
    }
}

void CaseViewModel::setVisible(bool isVisible)
{
    for (auto &pline : pline_nodes_)
    {
        pline->setVisible(isVisible);
    }
}

bool CaseViewModel::isVisible() const
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

void CaseViewModel::setDrawStyle(const DrawStyle &drawstyle)
{
    for (auto &pline : pline_nodes_)
    {
        pline->setDrawStyle(drawstyle);
    }
}
} // namespace debugger
