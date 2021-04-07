import FWCore.ParameterSet.Config as cms

ctppsDiamondRawData = cms.EDProducer(
    "CTPPSDiamondDigiToRaw",
    InputLabel=cms.InputTag("RDimDetDigitizer")
)
