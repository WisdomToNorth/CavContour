#include "DocData.h"

#include <cmath>
#include <iostream>
namespace debugger
{

DocData::DocData(const SCaseData &data)
    : scase_data_(data)
    , raw_data_type_(RawDataType::SData)
{
    // convert spline to pline
    for (const auto &[spline, type] : scase_data_)
    {
        Pline pline;
        PlineUtils::SPlineToPline(spline, pline);
        case_data_.push_back(std::make_pair(pline, type));
    }
}

DocData::DocData(const CaseData &data)
    : case_data_(data)
    , raw_data_type_(RawDataType::Data)
{
}

void DocData::getSData(SCaseData &data)
{
    for (const auto &[pline, type] : case_data_)
    {
        SPline spline;
        PlineUtils::PlineToSPline(pline, spline);
        scase_data_.push_back(std::make_pair(spline, type));
    }
    data = scase_data_;
}

void DocData::getData(CaseData &data)
{
    data = case_data_;
}

CaseViewModel *DocData::getVMData()
{
    if (!pre_calc_viewdata_)
    {
        pre_calc_viewdata_ = raw_data_type_ == RawDataType::SData ? buildVMFromSCase(scase_data_) :
                                                                    buildVMFromCase(case_data_);
    }
    return pre_calc_viewdata_;
}

// return data index of segment
std::vector<std::tuple<size_t, size_t, size_t>> DocData::hitTest(const double x, const double y,
                                                                 const double tol)
{
    return hitTestCaseData(x, y, tol);
}

std::vector<std::tuple<size_t, size_t, size_t>>
DocData::hitTestSCaseData(const double x, const double y, const double tol)
{
    std::vector<std::tuple<size_t, size_t, size_t>> res;
    for (size_t i = 0; i < scase_data_.size(); i++)
    {
        const SPline &pline = scase_data_[i].first;
        for (size_t j = 0; j < pline.size(); j++)
        {
            const SRecordF &record = pline[j];
            if (ptSame(record.x, record.y, x, y, tol))
            {
                res.emplace_back(i, j, 0);
                if (j > 0)
                {
                    res.emplace_back(i, j - 1, 1);
                }
            }
        }
    }
    return res;
}

std::vector<std::tuple<size_t, size_t, size_t>>
DocData::hitTestCaseData(const double x, const double y, const double tol)
{
    std::vector<std::tuple<size_t, size_t, size_t>> res;
    for (size_t i = 0; i < case_data_.size(); i++)
    {
        const Pline &pline = case_data_[i].first;
        for (size_t j = 1; j < pline.size(); j++)
        {
            const RecordF &record = pline[j];
            if (ptSame(record.x0, record.y0, x, y, tol))
            {
                res.emplace_back(i, j, 0);
            }
            if (ptSame(record.x1, record.y1, x, y, tol))
            {
                res.emplace_back(i, j, 1);
            }
        }
    }
    return res;
}

void DocData::setEditing(const std::vector<std::tuple<size_t, size_t, size_t>> &index)
{
    editing_ = index;
}

void DocData::resetEditing()
{
    editing_.clear();
}

void DocData::editData(const double x, const double y, const double tol)
{
    editCaseData(x, y, tol);
}

CaseViewModel *DocData::buildVMFromSCase(const SCaseData &data)
{
    ViewData viewdata(data.size());
    for (size_t i = 0; i < data.size(); i++)
    {
        const auto &[spline, is_hole] = data[i];
        Pline pline;
        PlineUtils::SPlineToPline(spline, pline);
        viewdata[i] = pline;
    }

    return new CaseViewModel(viewdata);
}

CaseViewModel *DocData::buildVMFromCase(const CaseData &casedata)
{
    ViewData viewdata(casedata.size());
    for (size_t i = 0; i < casedata.size(); i++)
    {
        const auto &[pline, is_hole] = casedata[i];
        viewdata[i] = pline;
    }
    return new CaseViewModel(viewdata);
}

void DocData::editSCaseData(const double x, const double y)
{
    // TODO: edit spline data together
    return editCaseData(x, y, 0.0);
}

bool DocData::ptSame(const double x0, const double y0, const double x, const double y,
                     const double tol)
{
    double dx = x0 - x;
    double dy = y0 - y;
    double dist = std::sqrt(dx * dx + dy * dy);
    return dist < tol;
};

void DocData::editCaseData(const double x, const double y, const double tol)
{
    for (auto [pline_index, seg_index, pt_index] : editing_)
    {
        if (pline_index >= case_data_.size())
        {
            assert(false);
            continue;
        }
        Pline &pline = case_data_[pline_index].first;

        if (seg_index >= pline.size())
        {
            assert(false);
            continue;
        }
        RecordF &record = pline[seg_index];

        if (pt_index == 0)
        {
            record.x0 = x;
            record.y0 = y;
        }
        else if (pt_index == 1)
        {
            record.x1 = x;
            record.y1 = y;
        }
        else
        {
            assert(false);
            continue;
        }
    }

    if (pre_calc_viewdata_)
    {
        std::vector<PlineGraphicItem *> &plinenodes = pre_calc_viewdata_->plineNodes();
        for (auto [pline_index, seg_index, pt_index] : editing_)
        {
            if (pline_index >= plinenodes.size())
            {
                assert(false);
                continue;
            }
            Pline &pline = case_data_[pline_index].first;
            PlineGraphicItem *plineitem = plinenodes[pline_index];
            plineitem->updateNode(seg_index, pline[seg_index]);
        }
    }
}
} // namespace debugger
