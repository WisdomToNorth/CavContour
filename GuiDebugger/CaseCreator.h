#ifndef CASECREATOR_H
#define CASECREATOR_H
#include <string>

namespace debugger
{
class DocData;
struct CaseCreator
{
public:
    static DocData *createData(const std::string &name);

private:
    static DocData *buildCase0();
    static DocData *buildCase1();
    static DocData *buildCase2();
    static DocData *buildCase3();
};
} // namespace debugger
#endif // CASEDATA_H
