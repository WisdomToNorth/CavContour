#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <string>

#include "DocData.h"

namespace debugger
{

class DocManager
{
public:
    static DocManager &instance()
    {
        static DocManager instance;
        return instance;
    }

    bool setCurDoc(const std::string &doc_name);
    bool setCurDoc(size_t index);
    DocData *getCurDoc();

private:
    std::unordered_map<size_t, std::string> doc_name_;
    std::unordered_map<std::string, DocData *> doc_data_;
    DocData *cur_doc_ = nullptr;

private:
    DocManager() = default;
    ~DocManager() = default;
};

} // namespace debugger
#endif // CASEDATA_H
