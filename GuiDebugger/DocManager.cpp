
#include "DocManager.h"

#include "viewer/caseviewmodel.h"

#include "CaseCreator.h"

namespace debugger
{
bool DocManager::setCurDoc(const std::string &doc_name)
{
    DocData *doc = nullptr;
    if (doc_data_.find(doc_name) == doc_data_.end())
    {
        doc = CaseCreator::createData(doc_name);
        if (doc)
        {
            doc_data_[doc_name] = doc;
            doc_name_[doc_data_.size()] = doc_name;
        }
    }
    else
    {
        doc = doc_data_[doc_name];
    }
    cur_doc_ = doc;
    return doc != nullptr;
}

bool DocManager::setCurDoc(size_t index)
{
    if (doc_name_.find(index) != doc_name_.end())
    {
        return setCurDoc(doc_name_[index]);
    }
    return false;
}

DocData *DocManager::getCurDoc()
{
    return cur_doc_;
}
} // namespace debugger
