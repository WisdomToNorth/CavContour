#include "CaseCreator.h"

#include <cmath>
#include <unordered_map>

#include "DocData.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

namespace debugger
{
DocData *CaseCreator::createData(const std::string &name)
{
    std::unordered_map<std::string, int> datamap{
        {"case0", 0}, {"case1", 1}, {"case2", 2}, {"case3", 3}};

    if (datamap.contains(name))
    {
        auto index = datamap[name];
        switch (index)
        {
        case 0: return buildCase0();
        case 1: return buildCase1();
        case 2: return buildCase2();
        case 3: return buildCase3();
        default: break;
        }
    }
    return nullptr;
}

DocData *CaseCreator::buildCase0()
{
    CaseData data;
    RecordF segment1{0, 1, 2, 1, 1, 1, 1.0, true, false};
    RecordF segment2{2, 1, 1.6, 1.8, 0, 0, 0, true, true};
    RecordF segment3{1.6, 1.8, 1, 2, 0, 0, 0, true, true};
    RecordF segment4{1, 2, 0.2, 1.6, 0, 0, 0, true, true};
    RecordF segment5{0.2, 1.6, 0, 1, 0, 0, 0, true, true};
    Pline pline1{segment1, segment2, segment3, segment4, segment5};
    data.push_back(std::make_pair(pline1, false));
    DocData *doc_data = new DocData(data);
    return doc_data;
}

DocData *CaseCreator::buildCase1()
{
    SCaseData case_data;
    /*outboundry*/
    // auto radius = 40;
    // auto centerX = 0;
    // auto centerY = 0;
    // std::size_t segmentCount = 16;
    // std::vector<SRecordF> data1;
    // for (std::size_t i = 0; i < segmentCount; ++i)
    // {
    //     double angle = 2 * M_PI / segmentCount;
    //     data1.push_back(SRecordF{radius * std::cos(angle) + centerX,
    //                              radius * std::sin(angle) + centerY, (i % 2 == 0 ? 1.0 : -1.0)});
    // }
    // data1.push_back(data1[0]);

    /*hole*/
    std::vector<SRecordF> data2{SRecordF{-7, -25, 0}, SRecordF{-4, -25, 0}, SRecordF{-4, -15, 0},
                                SRecordF{-7, -15, 0}, SRecordF{-7, -25, 0}};

    // /*hole*/
    // std::vector<SRecordF> data3{SRecordF{22, -20, 1}, SRecordF{27, -20, 1}, SRecordF{22, -20,
    // 1}};

    /*hole*/
    std::vector<SRecordF> data4{SRecordF{0, 25, 1},
                                SRecordF{-4, 0, 0},
                                SRecordF{2, 0, 1},
                                SRecordF{10, 0, -0.5},
                                SRecordF{8, 9, 0.374794619217547},
                                SRecordF{21, 0, 0},
                                SRecordF{23, 0, 1},
                                SRecordF{32, 0, -0.5},
                                SRecordF{28, 0, 0.5},
                                SRecordF{28, 12, 0.5},
                                SRecordF{0, 25, 1}};

    // case_data.push_back(std::make_pair(data1, false));
    case_data.push_back(std::make_pair(data2, false));
    // case_data.push_back(std::make_pair(data3, true));
    case_data.push_back(std::make_pair(data4, false));
    DocData *doc_data = new DocData(case_data);
    return doc_data;
}

DocData *CaseCreator::buildCase2()
{
    SCaseData case_data;

    /*outboundry*/
    std::vector<SRecordF> data1{SRecordF{0, 0, 0}, SRecordF{0, 10, 0}, SRecordF{10, 10, 0},
                                SRecordF{10, 0, 0}, SRecordF{0, 0, 0}};

    /*hole*/
    std::vector<SRecordF> data2{SRecordF{2, 2, 1}, SRecordF{2, 8, 1}, SRecordF{2, 2, 1}};

    case_data.push_back(std::make_pair(data1, true));
    case_data.push_back(std::make_pair(data2, false));
    DocData *doc_data = new DocData(case_data);
    return doc_data;
}

DocData *CaseCreator::buildCase3()
{
    SCaseData case_data;

    /*outboundry*/
    for (double i = 5.0; i < 1000.01; i = i + 1.0)
    {
        std::vector<SRecordF> data{SRecordF{-i, -i, 0}, SRecordF{i, -i, 0}, SRecordF{i, i, 0},
                                   SRecordF{-i, i, 0}, SRecordF{-i, -i, 0}};
        case_data.push_back(std::make_pair(data, false));
    }

    DocData *doc_data = new DocData(case_data);
    return doc_data;
}
} // namespace debugger
