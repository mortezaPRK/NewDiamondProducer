import FWCore.ParameterSet.Config as cms

from SimPPS.PPSDiamondDigiProducer.DiamondDetDigitizer_cfi import *

ctppsDigiTask = cms.Task(DiamondDetDigitizer)
ctppsDiamondDigiTask = cms.Task(DiamondDetDigitizer)

ctppsDigi = cms.Sequence(DiamondDetDigitizer)
