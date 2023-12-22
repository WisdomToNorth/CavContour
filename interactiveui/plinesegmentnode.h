#ifndef PLINESEGMENTNODE_H
#define PLINESEGMENTNODE_H

#include "cavc/polyline.hpp"
#include "flatcolorgeometrynode.h"

class PlineSegmentNode : public FlatColorGeometryNode {
public:
  PlineSegmentNode();
  void updateGeometry(cavc::PlineVertex<double> const &v1, cavc::PlineVertex<double> const &v2,
                      double arcApproxError = 0.01);
};

#endif // PLINESEGMENTNODE_H
