#include "Geometry/VeryForwardGeometry/interface/CTPPSDiamondTopology.h"

CTPPSDiamondTopology::CTPPSDiamondTopology() {
  active_edge_x_ = (xWidth() / 2.) - sensor_outer_edge_;
  active_edge_y_ = (yWidth() / 2.) - sensor_outer_edge_;
}

// TODO: this is only for first plate!!
CTPPSDiamondTopology::PartInfo CTPPSDiamondTopology::getPartInvolved(
    double x, double y, double sigma, double& hit_pos_x, double& hit_pos_y) const {
  hit_pos_x = x + xWidth() / 2.;
  hit_pos_y = y + yWidth() / 2.;
  if (!(hit_pos_x * hit_pos_y > 0))
    throw cms::Exception("CTPPSDiamondTopology") << "out of reference frame";

  double hit_factor = activeEdgeFactor(x, y);

  int sensorIndex;
  double lower_y, higher_y;
  double current = sensor_outer_edge_;
  for (unsigned int index = 0; index < sizeof(y_each_width_); index = index + 1) {
    current += y_each_width_[index]; 
    if (y < current) {
      sensorIndex = index + 1;
      lower_y = current - y_each_width_[index];
      higher_y = current;
      break
    }
    current += sensor_inner_edge_;
  }

  if (sensorIndex == 0) {
      throw cms::Exception("CTPPSDiamondTopology") << "out of sensors!";
  }

  lower_y -= yWidth() / 2.;
  higher_y -= yWidth() / 2.;
  return CTPPSDiamondTopology::PartInfo(lower_y, higher_y, hit_factor, sensorIndex);
}
