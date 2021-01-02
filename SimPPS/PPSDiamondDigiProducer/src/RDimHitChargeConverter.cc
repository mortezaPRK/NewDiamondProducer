#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "DataFormats/GeometryVector/interface/LocalPoint.h"
#include "SimPPS/PPSDiamondDigiProducer/interface/RDimLinearChargeDivider.h"
#include "SimPPS/PPSDiamondDigiProducer/interface/RDimHitChargeConverter.h"
#include "SimPPS/PPSDiamondDigiProducer/interface/RDimChargeShare.h"

RDimHitChargeConverter::RDimHitChargeConverter(const edm::ParameterSet &params,
                                               CLHEP::HepRandomEngine &eng,
                                               uint32_t det_id)
    : det_id_(det_id) {
  verbosity_ = params.getParameter<int>("RDimVerbosity");
  theRDimChargeDivider = std::make_unique<RDimLinearChargeDivider>(params, eng, det_id);
  theRDimChargeCollectionDrifter = std::make_unique<RDimLinearChargeCollectionDrifter>(params, det_id);
  theRDimChargeShare = std::make_unique<RDimChargeShare>(params, det_id);
}

//
// Converts a hit to number of inducted electrons in the specified part
//
std::map<unsigned short, double> RDimHitChargeConverter::processHit(const PSimHit &hit) {
  std::vector<RDimEnergyDepositUnit> ions_along_path = theRDimChargeDivider->divide(hit);
  if (verbosity_)
    edm::LogInfo("RDimHitChargeConverter") << det_id_ << " clouds no generated on the path=" << ions_along_path.size();
  return theRDimChargeShare->Share(theRDimChargeCollectionDrifter->Drift(ions_along_path));
}
