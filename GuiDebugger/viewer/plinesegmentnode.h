#ifndef PLINESEGMENTNODE_H
#define PLINESEGMENTNODE_H

#include "viewer/flatcolorgeometrynode.h"

#include "cavc/polyline.hpp"

namespace debugger
{
class PlineSegmentNode : public FlatColorGeometryNode
{
public:
    PlineSegmentNode(){};
    void updateGeometry(cavc::PlineVertex<double> const &v1, cavc::PlineVertex<double> const &v2,
                        double arcApproxError = 0.01);
};
} // namespace debugger
#endif // PLINESEGMENTNODE_H
