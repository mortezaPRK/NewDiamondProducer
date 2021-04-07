# Auto generated configuration file
# using:
# Revision: 1.19
# Source: /local/reps/CMSSW/CMSSW/Configuration/Applications/python/ConfigBuilder.py,v
# with command line options: step2 --filein=file:GluGluTo2Jets_M_300_2000_13TeV_exhume_cff_py_GEN_SIM_HECTOR_CTPPS.root --conditions auto:run2_mc -s DIGI:pdigi_valid,DIGI2RAW --datatier GEN-SIM-DIGI-RAW -n 10 --era Run2_2016 --eventcontent FEVTDEBUG --no_exec
from Configuration.StandardSequences.earlyDeleteSettings_cff import customiseEarlyDelete
from HLTrigger.Configuration.customizeHLTforMC import customizeHLTforMC
from PhysicsTools.PatAlgos.tools.helpers import associatePatAlgosToolsTask
from Configuration.AlCa.GlobalTag import GlobalTag
import FWCore.ParameterSet.Config as cms

from Configuration.StandardSequences.Eras import eras
process = cms.Process('DIGI2RAW', eras.Run2_2017)

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')  #
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')  #
process.load('FWCore.MessageService.MessageLogger_cfi')  #
process.load('Configuration.EventContent.EventContent_cff')  #
process.load('SimGeneral.MixingModule.mixNoPU_cfi')  #
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')  #
process.load('Configuration.StandardSequences.MagneticField_cff')  #
process.load('Configuration.StandardSequences.cmsCTPPSDigi_cff')  # <--
process.load('Configuration.StandardSequences.SimL1Emulator_cff')  #
# process.load('Configuration.StandardSequences.cmsCTPPSDigiToRaw_cff')  # <--
# process.load('HLTrigger.Configuration.HLT_2e34v31_cff')  #
process.load('Configuration.StandardSequences.EndOfProcess_cff')  #
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')  #
process.load('Configuration.Geometry.GeometryExtended2017_CTPPS_cff')  #
# process.load("CondFormats.CTPPSReadoutObjects.CTPPSPixelDAQMappingESSourceXML_cfi")  # <--
# process.load("CondFormats.CTPPSReadoutObjects.CTPPSDiamondDAQMappingESSourceXML_cfi")  # <--
process.maxEvents = cms.untracked.PSet(input=cms.untracked.int32(-1))

process.load("IOMC.RandomEngine.IOMC_cff")
process.RandomNumberGeneratorService.generator.initialSeed = 456789
process.RandomNumberGeneratorService.g4SimHits.initialSeed = 9876
process.RandomNumberGeneratorService.VtxSmeared.initialSeed = 123456789
process.RandomNumberGeneratorService.RPixDetDigitizer = cms.PSet(
    initialSeed=cms.untracked.uint32(137137)
)
process.RandomNumberGeneratorService.RDimDetDigitizer = cms.PSet(
    initialSeed=cms.untracked.uint32(137137)
)

# Input source
process.source = cms.Source(
    "PoolSource",
    dropDescendantsOfDroppedBranches=cms.untracked.bool(False),
    fileNames=cms.untracked.vstring(
        'file:GluGlu_GEN_SIM_2017.root'
    ),
    inputCommands=cms.untracked.vstring(
        'keep *',
        'drop *_genParticles_*_*',
        'drop *_genParticlesForJets_*_*',
        'drop *_kt4GenJets_*_*',
        'drop *_kt6GenJets_*_*',
        'drop *_iterativeCone5GenJets_*_*',
        'drop *_ak4GenJets_*_*',
        'drop *_ak7GenJets_*_*',
        'drop *_ak8GenJets_*_*',
        'drop *_ak4GenJetsNoNu_*_*',
        'drop *_ak8GenJetsNoNu_*_*',
        'drop *_genCandidatesForMET_*_*',
        'drop *_genParticlesForMETAllVisible_*_*',
        'drop *_genMetCalo_*_*',
        'drop *_genMetCaloAndNonPrompt_*_*',
        'drop *_genMetTrue_*_*',
        'drop *_genMetIC5GenJs_*_*'),
    secondaryFileNames=cms.untracked.vstring()
)

# process.options = cms.untracked.PSet(
#     SkipEvent=cms.untracked.vstring('ProductNotFound')
# )

# Production Info
process.configurationMetadata = cms.untracked.PSet(
    annotation=cms.untracked.string('step2 nevts:10'),
    name=cms.untracked.string('Applications'),
    version=cms.untracked.string('$Revision: 1.19 $')
)

process.es_prefer = cms.ESPrefer('TrackerGeometricDetESModule', 'trackerNumberingGeometry')
# Output definition

process.FEVTDEBUGHLToutput = cms.OutputModule(
    "PoolOutputModule",
    dataset=cms.untracked.PSet(
        dataTier=cms.untracked.string('GEN-SIM-DIGI-RAW'),
        filterName=cms.untracked.string('')
    ),
    eventAutoFlushCompressedSize=cms.untracked.int32(5242880),
    fileName=cms.untracked.string('gluglu_step2_DIGI_DIGI2RAW.root'),
    outputCommands=process.FEVTDEBUGHLTEventContent.outputCommands +
    [
        'keep *_RPixDetDigitizer_*_*',
        'keep *_ctppsPixelRawData_*_*',
        'keep *_RDimDetDigitizer_*_*',
        'keep *_ctppsDiamondRawData_*_*'
    ],
    splitLevel=cms.untracked.int32(0)
)

# Additional output definition

# Other statements
process.mix.digitizers = cms.PSet(process.theDigitizersValid)
process.GlobalTag = GlobalTag(
    process.GlobalTag,
    'auto:phase1_2017_realistic',
    ''
)

# Path and EndPath definitions
process.digitisation_step = cms.Path(process.pdigi_valid)
process.L1simulation_step = cms.Path(process.SimL1Emulator)
# process.digi2raw_step = cms.Path(process.DigiToRaw)
process.endjob_step = cms.EndPath(process.endOfProcess)
process.FEVTDEBUGHLToutput_step = cms.EndPath(process.FEVTDEBUGHLToutput)

# Schedule definition
process.schedule = cms.Schedule(
    process.digitisation_step,
    process.L1simulation_step,
    # process.digi2raw_step
)
# process.schedule.extend(process.HLTSchedule)
process.schedule.extend([process.endjob_step, process.FEVTDEBUGHLToutput_step])
associatePatAlgosToolsTask(process)


# Automatic addition of the customisation function from HLTrigger.Configuration.customizeHLTforMC

# call to customisation function customizeHLTforMC imported from HLTrigger.Configuration.customizeHLTforMC
process = customizeHLTforMC(process)


# Add early deletion of temporary data products to reduce peak memory need
process = customiseEarlyDelete(process)
# End adding early deletion
# print process.dumpPython()