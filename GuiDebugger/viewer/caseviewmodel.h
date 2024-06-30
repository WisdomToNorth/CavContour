#ifndef VIEWMODEL_H
#define VIEWMODEL_H

#include <vector>

#include "PlineGraphicItem.h"
#include "drawstyle.h"
#include "vmparameter.h"

namespace debugger
{
class CaseViewModel
{
public:
    CaseViewModel();
    CaseViewModel(const ViewData &viewdata);
    ~CaseViewModel();

    void updateData(const ViewData &viewdata);
    void clearData();

    std::vector<PlineGraphicItem *> getPlineNodes()
    {
        return pline_nodes_;
    }
    std::vector<PlineGraphicItem *> &plineNodes()
    {
        return pline_nodes_;
    }

public:
    void setDrawStyle(const DrawStyle &drawstyle);
    void setVisible(bool isVisible);
    bool isVisible() const;

private:
    std::vector<PlineGraphicItem *> pline_nodes_;
};

} // namespace debugger
#endif // NgViewModel_H
