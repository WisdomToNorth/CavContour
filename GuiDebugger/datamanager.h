#ifndef DATAMANAGER_H
#define DATAMANAGER_H
#include <QString>

#include "casedata.h"

namespace debugger
{

class DocumetData
{
public:
    SCaseData case_data_;
    QString case_index_;

    static DocumetData &getInstance()
    {
        static DocumetData instance;
        return instance;
    }

private:
    DocumetData() = default;
    ~DocumetData() = default;
};

} // namespace debugger
#endif // CASEDATA_H
