#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <string>

#include <QString>

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

    /**
     * Will also add to doc_name_ and doc_data_ if not already present
     */
    DocData *loadFile(const QString &filename);
    /**
     * Returns false if no current doc
     */
    bool saveCurFile(const QString &filename);

    bool setCurDoc(const std::string &doc_name);
    bool setCurDoc(size_t index);
    /*Only docs imported from DocManager can be set as current doc*/
    void setAsCurDoc(DocData *doc);
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
