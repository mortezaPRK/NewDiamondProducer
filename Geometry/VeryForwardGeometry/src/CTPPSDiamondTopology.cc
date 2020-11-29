#include "Geometry/VeryForwardGeometry/interface/CTPPSDiamondTopology.h"

CTPPSDiamondTopology::PartInfo CTPPSDiamondTopology::getPartInvolved(
    double x, double y, double sigma, double& hit_pos_x, double& hit_pos_y) const {
      
  // TODO: return info about involved part of det

  return CTPPSDiamondTopology::PartInfo(low_pixel_range_x,
                                          high_pixel_range_x,
                                          low_pixel_range_y,
                                          high_pixel_range_y,
                                          hit_factor,
                                          part_index);
}
