
#include "DocManager.h"

#include <iostream>

#include <QFileInfo>

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

void DocManager::setAsCurDoc(DocData *doc)
{
    if (doc == nullptr || doc_data_.find(doc->getName()) == doc_data_.end())
    {
        return;
    }

    cur_doc_ = doc;
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

DocData *DocManager::loadFile(const QString &filepath)
{
    QFileInfo file(filepath);
    QString name = file.baseName();
    if (doc_data_.find(name.toStdString()) == doc_data_.end())
    {
        DocData *doc = DocData::load(filepath, name);
        if (doc)
        {
            doc_data_[name.toStdString()] = doc;
            doc_name_[doc_data_.size()] = name.toStdString();
        }
        else
        {
            return nullptr;
        }
    }

    return doc_data_[name.toStdString()];
}

bool DocManager::saveCurFile(const QString &filename)
{
    if (cur_doc_)
    {
        std::cout << "saveFile: " << filename.toStdString() << std::endl;
        return true;
    }
    std::cout << "saveFile: " << filename.toStdString() << std::endl;
    return false;
}
} // namespace debugger
