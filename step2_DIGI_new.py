# Auto generated configuration file
# using: 
# Revision: 1.19 
# Source: /local/reps/CMSSW/CMSSW/Configuration/Applications/python/ConfigBuilder.py,v 
# with command line options: step2 --filein=file:GluGlu_GEN_SIM_2017.root --conditions auto:phase1_2021_realistic -s DIGI --datatier GEN-SIM-DIGI-RAW -n 10 --era Run3 --eventcontent FEVTDEBUG --no_exec
import FWCore.ParameterSet.Config as cms

from Configuration.Eras.Era_Run3_cff import Run3

process = cms.Process('DIGI',Run3)

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('SimGeneral.MixingModule.mixNoPU_cfi')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_cff')
process.load('Configuration.StandardSequences.Digi_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
# process.load('Configuration.Geometry.GeometryExtended2021_cff')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1),
)


process.load("IOMC.RandomEngine.IOMC_cff")
process.RandomNumberGeneratorService.generator.initialSeed = 456789
process.RandomNumberGeneratorService.g4SimHits.initialSeed = 9876
process.RandomNumberGeneratorService.VtxSmeared.initialSeed = 123456789
process.RandomNumberGeneratorService.DiamondDetDigitizer = cms.PSet(initialSeed =cms.untracked.uint32(137137))

# Input source
process.source = cms.Source("PoolSource",
    dropDescendantsOfDroppedBranches = cms.untracked.bool(False),
    fileNames = cms.untracked.vstring('file:GluGlu_step1_GEN_SIM_2021.root'),
    inputCommands = cms.untracked.vstring(
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
        'drop *_genMetIC5GenJs_*_*'
    ),
    secondaryFileNames = cms.untracked.vstring()
)

process.options = cms.untracked.PSet(
#     FailPath = cms.untracked.vstring(),
#     IgnoreCompletely = cms.untracked.vstring(),
#     Rethrow = cms.untracked.vstring(),
#     SkipEvent = cms.untracked.vstring(),
#     allowUnscheduled = cms.obsolete.untracked.bool,
#     canDeleteEarly = cms.untracked.vstring(),
#     emptyRunLumiMode = cms.obsolete.untracked.string,
#     eventSetup = cms.untracked.PSet(
#         forceNumberOfConcurrentIOVs = cms.untracked.PSet(

#         ),
#         numberOfConcurrentIOVs = cms.untracked.uint32(1)
#     ),
#     fileMode = cms.untracked.string('FULLMERGE'),
#     forceEventSetupCacheClearOnNewRun = cms.untracked.bool(False),
#     makeTriggerResults = cms.obsolete.untracked.bool,
#     numberOfConcurrentLuminosityBlocks = cms.untracked.uint32(1),
#     numberOfConcurrentRuns = cms.untracked.uint32(1),
#     numberOfStreams = cms.untracked.uint32(0),
#     numberOfThreads = cms.untracked.uint32(1),
#     printDependencies = cms.untracked.bool(False),
#     sizeOfStackForThreadsInKB = cms.optional.untracked.uint32,
#     throwIfIllegalParameter = cms.untracked.bool(True),
#     wantSummary = cms.untracked.bool(False)
    deleteNonConsumedUnscheduledModules = cms.untracked.bool(True)
)

# Production Info
process.configurationMetadata = cms.untracked.PSet(
    annotation = cms.untracked.string('step2 nevts:10'),
    name = cms.untracked.string('Applications'),
    version = cms.untracked.string('$Revision: 1.19 $')
)

# Output definition

process.FEVTDEBUGoutput = cms.OutputModule("PoolOutputModule",
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string('GEN-SIM-DIGI-RAW'),
        filterName = cms.untracked.string('')
    ),
    fileName = cms.untracked.string('step2_DIGI.root'),
    outputCommands = process.FEVTDEBUGEventContent.outputCommands + [
        "keep CTPPSDiamondDigiedmDetSetVector_*_*_*",
    ],
    splitLevel = cms.untracked.int32(0)
)

# Additional output definition

# Other statements
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:phase1_2021_realistic', '')
# process.content = cms.EDAnalyzer("EventContentAnalyzer")
# process.Tracer = cms.Service("Tracer")
# process.eca = cms.Path(process.content)
# Path and EndPath definitions
# process.digitisation_step = cms.Path(process.mix*process.DiamondDetDigitizer)
process.digitisation_step = cms.Path(process.DiamondDetDigitizer)
# process.digitisation_step = cms.Path(process.pdigi * process.content)
# process.digitisation_step = cms.Path(process.pdigi)
process.endjob_step = cms.EndPath(process.endOfProcess)
process.FEVTDEBUGoutput_step = cms.EndPath(process.FEVTDEBUGoutput)

# Schedule definition
process.schedule = cms.Schedule(process.digitisation_step,process.endjob_step,process.FEVTDEBUGoutput_step)
from PhysicsTools.PatAlgos.tools.helpers import associatePatAlgosToolsTask
associatePatAlgosToolsTask(process)


# Customisation from command line

# Add early deletion of temporary data products to reduce peak memory need
from Configuration.StandardSequences.earlyDeleteSettings_cff import customiseEarlyDelete
process = customiseEarlyDelete(process)
# End adding early deletion
