#ifndef DOCDATA_H
#define DOCDATA_H

#include <optional>
#include <tuple>

#include "viewer/caseviewmodel.h"
#include "viewer/vmparameter.h"

namespace debugger
{
typedef bool IsHole; // cw
typedef std::vector<std::pair<SPline, IsHole>> SCaseData;
typedef std::vector<std::pair<Pline, IsHole>> CaseData;

class DocData
{
private:
    enum class RawDataType
    {
        SData,
        Data
    };
    const RawDataType raw_data_type_;
    SCaseData scase_data_;
    CaseData case_data_;

    CaseViewModel *pre_calc_viewdata_ = nullptr;
    std::vector<std::tuple<size_t, size_t, size_t>> editing_;

public:
    DocData(const SCaseData &data);
    DocData(const CaseData &data);

    void getSData(SCaseData &data);
    void getData(CaseData &data);

    // return data index of pline, index of segment
    std::vector<std::tuple<size_t, size_t, size_t>> hitTest(const double x, const double y,
                                                            const double tol);
    void setEditing(const std::vector<std::tuple<size_t, size_t, size_t>> &index);
    void resetEditing();
    void editData(const double x, const double y, const double tol);

    CaseViewModel *getVMData();

private:
    static CaseViewModel *buildVMFromSCase(const SCaseData &casedata);
    static CaseViewModel *buildVMFromCase(const CaseData &casedata);

    std::vector<std::tuple<size_t, size_t, size_t>> hitTestSCaseData(const double x, const double y,
                                                                     const double tol);
    std::vector<std::tuple<size_t, size_t, size_t>> hitTestCaseData(const double x, const double y,
                                                                    const double tol);
    void editSCaseData(const double x, const double y);
    void editCaseData(const double x, const double y, const double tol);
    static bool ptSame(const double x0, const double y0, const double x, const double y,
                       const double tol);
};
} // namespace debugger
#endif // CASEDATA_H
