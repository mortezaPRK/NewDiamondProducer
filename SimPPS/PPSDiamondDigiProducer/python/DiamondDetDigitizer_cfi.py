import FWCore.ParameterSet.Config as cms

DiamondDetDigitizer = cms.EDProducer(
    "CTPPSDiamondDigiProducer",
    DiamondVerbosity=cms.int32(0),
    mixLabel=cms.string("mix"),
    InputCollection=cms.string("g4SimHitsPPSDiamondHits")
)
