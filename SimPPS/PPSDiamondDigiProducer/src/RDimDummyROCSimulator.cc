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

  capacitor_ = params.getParameter<double>("RDimCapacitor");
  transmit_time_ = params.getParameter<double>("RDimTransmitTime");
  resistor_ = params.getParameter<double>("RDimResistor");
}

void RDimDummyROCSimulator::ConvertChargeToHits(
    const std::vector<std::pair<double, double>> &signals,
    std::map<unsigned short, std::vector<std::pair<int, double>>> &theSignalProvenance,
    std::vector<CTPPSDiamondDigi> &output_digi,
    std::vector<std::vector<std::pair<int, double>>> &output_digi_links) {
  int input_size = signals.size();
  for (int i = 0; i < input_size; ++i) {
    std::pair<double, double> signal = signals[i];
    double vmax = calculateMaximumVoltage(signal.first);
    double ledge, tedge;
    calculateEdges(vmax, signal.second, ledge, tedge);
    output_digi.push_back(CTPPSDiamondDigi(ledge, tedge, 0, true, 0));
  }
}

double RDimDummyROCSimulator::calculateMaximumVoltage(double charge) {
  double rc = resistor_ * capacitor_;
  return ((2.0 * charge * resistor_) / std::pow(transmit_time_, 2)) *
         (transmit_time_ * (rc * std::log(rc / (rc + transmit_time_))));
}

void RDimDummyROCSimulator::calculateEdges(double vmax, double timeOfFlight, double &ledge, double &tedge) {
  ledge = (0.2) * vmax;
  tedge = (0.2) * vmax;
}