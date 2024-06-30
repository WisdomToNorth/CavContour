#include "drawstyle.h"

namespace debugger
{

bool DrawStyle::operator==(const DrawStyle &other) const
{
    return color == other.color && linetype == other.linetype &&
           arcApproxError == other.arcApproxError && width == other.width &&
           visible == other.visible && useUInt32Index == other.useUInt32Index;
}

QColor DrawStyle::indexToColor(std::size_t index)
{
    switch (index % 11)
    {
    case 0: return QColor("red");
    case 1: return QColor("blue");
    case 2: return QColor("green");
    case 3: return QColor("magenta");
    case 4: return QColor("orange");
    case 5: return QColor("greenyellow");
    case 6: return QColor("olive");
    case 7: return QColor("turquoise");
    case 8: return QColor("purple");
    case 9: return QColor("crimson");
    case 10: return QColor("black");
    }

    return QColor("black");
}
} // namespace debugger
