#include "settings.h"

#include <iostream>

namespace debugger
{
NgSettings::AppAlgorithmCore NgSettings::g_machineType = NgSettings::AppAlgorithmCore::kCavc;
DrawStyle NgSettings::g_drawStyle = DrawStyle();

void NgSettings::setAppAlgorithmCore(AppAlgorithmCore appAlgorithmCore)
{
    if (g_machineType != appAlgorithmCore)
    {
        g_machineType = appAlgorithmCore;
        emit appAlgorithmCoreChanged(appAlgorithmCore);
        std::cout << "cur algorithm core: " << static_cast<int>(g_machineType) << std::endl;
    }
}
} // namespace debugger
