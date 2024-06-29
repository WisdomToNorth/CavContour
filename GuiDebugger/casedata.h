#ifndef CASEDATA_H
#define CASEDATA_H

#include <tuple>
#include <vector>

#include <QString>

#include "viewer/viewmodel.h"

namespace debugger
{
typedef bool IsHole; // cw
typedef std::vector<std::pair<SPline, IsHole>> SCaseData;
typedef std::vector<std::pair<Pline, IsHole>> CaseData;

struct DataUtils
{
public:
    static void createData(std::vector<NgViewModel *> &viewdata, QString caseindex);

public:
    static void buildVMFromSCase(const SCaseData &casedata, std::vector<NgViewModel *> &viewdata);
    static void buildVMFromCase(const CaseData &casedata, std::vector<NgViewModel *> &viewdata);

private:
    static void buildSCase1(SCaseData &data);
    static void buildSCase2(SCaseData &data);
    static void buildCase0(CaseData &data);
};
} // namespace debugger
#endif // CASEDATA_H
