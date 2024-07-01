#ifndef CASECREATOR_H
#define CASECREATOR_H
#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

namespace debugger
{
class DocData;
struct CaseCreator
{
public:
    static DocData *createData(const std::string &name);
    static std::unordered_map<std::string, std::function<DocData *()>> datamap;
    static std::vector<std::string> getCaseNames();

private:
    static DocData *buildCase0();
    static DocData *buildCase1();
    static DocData *buildCase2();
    static DocData *buildCase3();
    static DocData *buildCase4();
    static DocData *buildCase5();
    static DocData *buildCase6();
    static DocData *buildCase7();
    static DocData *buildCase8();
    static DocData *buildCase9();
};
} // namespace debugger
#endif // CASEDATA_H
