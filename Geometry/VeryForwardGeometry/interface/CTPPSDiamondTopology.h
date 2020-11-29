#ifndef Geometry_VeryForwardGeometry_CTPPSDiamondTopology_h
#define Geometry_VeryForwardGeometry_CTPPSDiamondTopology_h

class CTPPSDiamondTopology {
public:
  CTPPSDiamondTopology() = default;
  ~CTPPSDiamondTopology() = default;

  static constexpr double thickness_ = 0.23;
  static constexpr double simX_width_ = 16.6;
  static constexpr double simY_width_ = 24.4;
  static constexpr double dead_edge_width_ = 200E-3;
  static constexpr double dead_part_width_ = 200E-3;

  static bool isValidHit(float xLocalCoordinate, float yLocalCoordinate) {
    // TODO: check if hit is actually inside our detector
  }

  CTPPSDiamondIndices indices_;

  //  TODO: check https://github.com/CTPPS/cmssw/blob/FullSim_SimG4CMS-PPS/SimG4CMS/PPS/src/PPSDiamondOrganization.cc
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
    PartInfo(double lower_simX_border,
              double higher_simX_border,
              double lower_simY_border,
              double higher_simY_border,
              double eff_factor)
        : lower_simX_border_(lower_simX_border),
          higher_simX_border_(higher_simX_border),
          lower_simY_border_(lower_simY_border),
          higher_simY_border_(higher_simY_border),
          eff_factor_(eff_factor) {}

    inline double higherSimXBorder() const { return higher_simX_border_; }
    inline double lowerSimXBorder() const { return lower_simX_border_; }
    inline double higherSimYBorder() const { return higher_simY_border_; }
    inline double lowerSimYBorder() const { return lower_simY_border_; }
    inline double effFactor() const { return eff_factor_; }
    inline double partIndex() const { return eff_factor_; }
    

  private:
    double lower_simX_border_;
    double higher_simX_border_;
    double lower_simY_border_;
    double higher_simY_border_;
    double eff_factor_;
  };

};

#endif
