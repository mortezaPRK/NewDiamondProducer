import FWCore.ParameterSet.Config as cms

DiamondDetDigitizer = cms.EDProducer(
    "DiamondDigiProducer",
    # mixLabel=cms.string("mix"),
    InputCollection=cms.string("g4SimHitsCTPPSTimingHits"),
    RDimVerbosity=cms.int32(1),
)
