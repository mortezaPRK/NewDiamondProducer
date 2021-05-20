# import FWCore.ParameterSet.Config as cms


# ctppsDigiTask = cms.Task(DiamondDetDigitizer)
# ctppsDiamondDigiTask = cms.Task(DiamondDetDigitizer)

# ctppsDigi = cms.Sequence(DiamondDetDigitizer)

import FWCore.ParameterSet.Config as cms

# PPS Digitization
# from SimPPS.PPSPixelDigiProducer.RPixDetDigitizer_cfi import *
# from SimPPS.RPDigiProducer.RPSiDetDigitizer_cfi import *
# from CalibPPS.ESProducers.ppsTopology_cff import *
from SimPPS.PPSDiamondDigiProducer.DiamondDetDigitizer_cfi import *
# RPixDetDigitizerTask=cms.Task(RPixDetDigitizer)
# RPSiDetDigitizerTask=cms.Task(RPSiDetDigitizer)
RPDimDetDigitizerTask = cms.Task(DiamondDetDigitizer)
ctppsDigiTask = cms.Task()
# cms.Task(cms.TaskPlaceholder("mix"), ctppsDigiTask)

# The commented lines below NEED to be activated in order to insert PPS into Run2
# add PPS 2016 digi modules
from Configuration.Eras.Modifier_ctpps_2016_cff import ctpps_2016
ctpps_2016.toReplaceWith( ctppsDigiTask, RPDimDetDigitizerTask)

# add PPS 2017 digi modules
from Configuration.Eras.Modifier_ctpps_2017_cff import ctpps_2017
# ctpps_2017Task = cms.Task(RPixDetDigitizer,RPSiDetDigitizer)
ctpps_2017.toReplaceWith(ctppsDigiTask, RPDimDetDigitizerTask)

# add PPS 2018 digi modules
from Configuration.Eras.Modifier_ctpps_2018_cff import ctpps_2018
ctpps_2018.toReplaceWith(ctppsDigiTask, RPDimDetDigitizerTask)

from Configuration.Eras.Modifier_ctpps_2021_cff import ctpps_2021
ctpps_2021.toReplaceWith(ctppsDigiTask, RPDimDetDigitizerTask)
