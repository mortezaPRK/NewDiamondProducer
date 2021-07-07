#ifndef Geometry_VeryForwardGeometry_CTPPSDiamondTopology_h
#define Geometry_VeryForwardGeometry_CTPPSDiamondTopology_h

#include <FWCore/Utilities/interface/Exception.h>
#include <cmath>

class CTPPSDiamondTopology {
public:
  CTPPSDiamondTopology();
  ~CTPPSDiamondTopology() = default;
public:
  // CTPPSDiamondIndices indices_;

  //     ________
  //    |        |
  //    |        |
  //    |        |
  // 8  |________|
  //     ________
  //    |        |
  //    |        |
  // 7  |        |
  //    |________|
  //     ________
  //    |        |
  // 6  |________|
  //    |        |
  // 5  |________|
  //     ________
  // 4  |________|
  // 3  |________|
  // 2  |________|
  // 1  |________|
  class PartInfo {
  public:
    PartInfo(double lower_y_border, double higher_y_border, double eff_factor, int part_index)
        : lower_y_border_(lower_y_border),
          higher_y_border_(higher_y_border),
          eff_factor_(eff_factor),
          part_index_(part_index) {}

    inline double higherYBorder() const { return higher_y_border_; }
    inline double lowerYBorder() const { return lower_y_border_; }
    inline double effFactor() const { return eff_factor_; }
    inline double partIndex() const { return part_index_; }

  private:
    double lower_y_border_;
    double higher_y_border_;
    double eff_factor_;
    int part_index_;

  public:
    friend std::ostream& operator<<(std::ostream& output, const PartInfo& p);
  };

public:

  static constexpr double active_edge_sigma_ = 0.02;
  static constexpr double thickness_ = 0.23;
  static constexpr double sensor_outer_edge_ = 0.15;
  static constexpr double sensor_inner_edge_ = 0.1;
  static constexpr double x_width_ = 4.2;
  static constexpr double y_each_width_[8] = {
      0.7,
      0.83,
      1.02,
      1.35,
      1.75,
      2.35,
      4.2,
      4.2,
  };

  inline double yWidth() const {
    int numberOfSensors = sizeof(y_each_width_);
    double w = 0.;
    for (int i = 0; i < 8; i++) {
      w += y_each_width_[i];
    }
    return w + ((numberOfSensors - 1) * sensor_inner_edge_) + 2 * sensor_outer_edge_;
  }

  inline double xWidth() const { return x_width_ + 2 * sensor_outer_edge_; }

  inline double detThickness() const { return thickness_; }
  
  static bool isValidHit(float xLocalCoordinate, float yLocalCoordinate) {
    // if (xLocalCoordinate > xWidth() / 2. || xLocalCoordinate < -xWidth() / 2.) {
    //   return false
    // }
    // if (yLocalCoordinate > yWidth() / 2. || yLocalCoordinate < -yWidth() / 2.) {
    //   return false
    // }
    return true;
  }
  PartInfo getPartInvolved(double x, double y, double sigma) const;

private:
  double active_edge_x_;
  double active_edge_y_;

  inline double activeEdgeFactor(double x, double y) const {
    const double inv_sigma = 1. / active_edge_sigma_;  // precaching
    const double topEdgeFactor = std::erf(-distanceFromTopActiveEdge(x, y) * inv_sigma) * 0.5 + 0.5;
    const double bottomEdgeFactor = std::erf(-distanceFromBottomActiveEdge(x, y) * inv_sigma) * 0.5 + 0.5;
    const double rightEdgeFactor = std::erf(-distanceFromRightActiveEdge(x, y) * inv_sigma) * 0.5 + 0.5;
    const double leftEdgeFactor = std::erf(-distanceFromLeftActiveEdge(x, y) * inv_sigma) * 0.5 + 0.5;

    const double aEF = topEdgeFactor * bottomEdgeFactor * rightEdgeFactor * leftEdgeFactor;

    if (aEF > 1.)
      throw cms::Exception("CTPPSDiamondTopology") << " active edge factor > 1";

    return aEF;
  }

  inline double distanceFromTopActiveEdge(double x, double y) const { return (y - active_edge_y_); }
  inline double distanceFromBottomActiveEdge(double x, double y) const { return (-y - active_edge_y_); }
  inline double distanceFromRightActiveEdge(double x, double y) const { return (x - active_edge_x_); }
  inline double distanceFromLeftActiveEdge(double x, double y) const { return (-x - active_edge_x_); }
};

#endif
