import FWCore.ParameterSet.Config as cms

DiamondDetDigitizer = cms.EDProducer(
    "DiamondDigiProducer",
    InputCollection=cms.string("g4SimHitsCTPPSTimingHits"),
    
    RDimVerbosity=cms.int32(1),
    RDVerbosity=cms.int32(1),
    RPDiamondChargeDivisions=cms.int32(1),
    RDimGeVPerElectron=cms.double(1.0),
    RDimInterSmearing=cms.vdouble(0.011),
    RPixVerbosity=cms.int32(1),
    RDimDummyROCThreshold=cms.double(1.0),
    RDimDummyROCElectronPerADC=cms.double(1.0),
)
