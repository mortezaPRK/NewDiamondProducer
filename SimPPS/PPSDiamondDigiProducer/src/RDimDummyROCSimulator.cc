#include "SimPPS/PPSDiamondDigiProducer/interface/RDimDummyROCSimulator.h"
#include "Geometry/VeryForwardGeometry/interface/CTPPSDiamondTopology.h"

#include "DataFormats/CTPPSDigi/interface/CTPPSDiamondDigi.h"
#include <vector>
#include "TRandom.h"
#include <iostream>

RDimDummyROCSimulator::RDimDummyROCSimulator(const edm::ParameterSet &params, uint32_t det_id) : det_id_(det_id) {
  threshold_ = params.getParameter<double>("RDimDummyROCThreshold");
  electron_per_adc_ = params.getParameter<double>("RDimDummyROCElectronPerADC");
  verbosity_ = params.getParameter<int>("RDimVerbosity");
}

void RDimDummyROCSimulator::ConvertChargeToHits(
    const std::map<unsigned short, double> &signals,
    std::map<unsigned short, std::vector<std::pair<int, double> > > &theSignalProvenance,
    std::vector<CTPPSDiamondDigi> &output_digi,
    std::vector<std::vector<std::pair<int, double> > > &output_digi_links) {
  for (std::map<unsigned short, double>::const_iterator i = signals.begin(); i != signals.end(); ++i) {
    //one threshold per hybrid
    // unsigned short pixel_no = i->first;
    if (i->second > threshold_) {
      // float gain = 0;
      // float pedestal = 0;
      int adc = 0;
      // uint32_t col = pixel_no / 160;
      // uint32_t row = pixel_no % 160;

      adc = int(round(i->second / electron_per_adc_));
      /// set maximum for 8 bits adc
      if (adc >= maxADC_)
        adc = maxADC_;
      if (adc < 0)
        adc = 0;
        
      // output_digi.push_back(CTPPSDiamondDigi(0,0,0, true, 0));
    }
  }
}
