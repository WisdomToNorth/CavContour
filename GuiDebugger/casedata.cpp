#include "casedata.h"

#include <cmath>

#include <QMap>
#include <QString>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

namespace debugger
{
void DataUtils::createData(std::vector<NgViewModel *> &viewdata, QString caseindex)
{
    QMap<QString, int> case_sdata{{"default1", 1}, {"default2", 2}};
    QMap<QString, int> case_data{{"default0", 0}};
    if (case_sdata.contains(caseindex))
    {
        SCaseData sdata;
        auto index = case_sdata[caseindex];
        switch (index)
        {
        case 1: buildSCase1(sdata); break;
        case 2: buildSCase2(sdata); break;
        default: break;
        }
        buildVMFromSCase(sdata, viewdata);
    }
    else if (case_data.contains(caseindex))
    {
        CaseData data;
        switch (case_data[caseindex])
        {
        case 0: buildCase0(data); break;
        default: break;
        }
        buildVMFromCase(data, viewdata);
    }
}

void DataUtils::buildVMFromSCase(const SCaseData &data, std::vector<NgViewModel *> &viewdata)
{
    for (auto const &[spline, is_hole] : data)
    {
        Pline pline;
        VMParameterUtils::SPlineToPline(spline, pline);
        ViewData viewdata1{pline};
        viewdata.push_back(new NgViewModel(viewdata1));
    }
}

void DataUtils::buildVMFromCase(const CaseData &casedata, std::vector<NgViewModel *> &viewdata)
{
    for (auto const &[pline, is_hole] : casedata)
    {
        ViewData viewdata1{pline};
        viewdata.push_back(new NgViewModel(viewdata1));
    }
}

void DataUtils::buildCase0(CaseData &data)
{
    data.clear();
    VMParameter segment1{0, 1, 2, 1, 1, 1, 1.0, true, false};
    VMParameter segment2{2, 1, 1.6, 1.8, 0, 0, 0, true, true};
    VMParameter segment3{1.6, 1.8, 1, 2, 0, 0, 0, true, true};
    VMParameter segment4{1, 2, 0.2, 1.6, 0, 0, 0, true, true};
    VMParameter segment5{0.2, 1.6, 0, 1, 0, 0, 0, true, true};
    Pline pline1{segment1, segment2, segment3, segment4, segment5};
    data.push_back(std::make_pair(pline1, false));
}

void DataUtils::buildSCase1(SCaseData &case_data)
{
    case_data.clear();

    /*outboundry*/
    auto radius = 40;
    auto centerX = 0;
    auto centerY = 0;
    std::size_t segmentCount = 16;
    std::vector<VMSimpleParameter> data1;
    for (std::size_t i = 0; i < segmentCount; ++i)
    {
        double angle = 2 * M_PI / segmentCount;
        data1.push_back(VMSimpleParameter{radius * std::cos(angle) + centerX,
                                          radius * std::sin(angle) + centerY,
                                          (i % 2 == 0 ? 1.0 : -1.0)});
    }
    /*hole*/
    std::vector<VMSimpleParameter> data2{
        VMSimpleParameter{-7, -25, 0}, VMSimpleParameter{-4, -25, 0}, VMSimpleParameter{-4, -15, 0},
        VMSimpleParameter{-7, -15, 0}};

    /*hole*/
    std::vector<VMSimpleParameter> data3{VMSimpleParameter{22, -20, 1},
                                         VMSimpleParameter{27, -20, 1}};
    /*hole*/
    std::vector<VMSimpleParameter> data4{VMSimpleParameter{0, 25, 1},
                                         VMSimpleParameter{-4, 0, 0},
                                         VMSimpleParameter{2, 0, 1},
                                         VMSimpleParameter{10, 0, -0.5},
                                         VMSimpleParameter{8, 9, 0.374794619217547},
                                         VMSimpleParameter{21, 0, 0},
                                         VMSimpleParameter{23, 0, 1},
                                         VMSimpleParameter{32, 0, -0.5},
                                         VMSimpleParameter{28, 0, 0.5},
                                         VMSimpleParameter{28, 12, 0.5}};

    case_data.push_back(std::make_pair(data1, false));
    case_data.push_back(std::make_pair(data2, true));
    case_data.push_back(std::make_pair(data3, true));
    case_data.push_back(std::make_pair(data4, true));
}

void DataUtils::buildSCase2(SCaseData &case_data)
{
    case_data.clear();
    /*outboundry*/

    std::vector<VMSimpleParameter> data1{VMSimpleParameter{0, 0, 0}, VMSimpleParameter{0, 10, 0},
                                         VMSimpleParameter{10, 10, 0}, VMSimpleParameter{10, 0, 0},
                                         VMSimpleParameter{0, 0, 0}};

    /*hole*/
    std::vector<VMSimpleParameter> data2{VMSimpleParameter{2, 2, -1}, VMSimpleParameter{2, 8, -1},
                                         VMSimpleParameter{8, 8, -1}, VMSimpleParameter{8, 2, -1},
                                         VMSimpleParameter{2, 2, -1}};

    case_data.push_back(std::make_pair(data1, true));
    case_data.push_back(std::make_pair(data2, false));
}
} // namespace debugger
