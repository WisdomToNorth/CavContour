#ifndef VIEWMODEL_H
#define VIEWMODEL_H

#include <vector>

#include "PlineGraphicItem.h"
#include "drawstyle.h"
#include "vmparameter.h"
namespace debugger
{
class NgViewModel
{
public:
    NgViewModel();
    NgViewModel(const ViewData &viewdata);
    ~NgViewModel();

    void setData(const ViewData &viewdata);
    void update();
    void clearData();
    std::vector<PlineGraphicItem *> getNodes() const
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
