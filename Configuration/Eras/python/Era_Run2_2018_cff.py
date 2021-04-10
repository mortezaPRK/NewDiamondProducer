import FWCore.ParameterSet.Config as cms

from Configuration.Eras.Era_Run2_2017_cff import Run2_2017
from Configuration.Eras.Modifier_run2_HEPlan1_2017_cff import run2_HEPlan1_2017
from Configuration.Eras.Modifier_run2_CSC_2018_cff import run2_CSC_2018
from Configuration.Eras.Modifier_run2_HB_2018_cff import run2_HB_2018
from Configuration.Eras.Modifier_run2_HE_2018_cff import run2_HE_2018
from Configuration.Eras.Modifier_run2_HCAL_2018_cff import run2_HCAL_2018
from Configuration.Eras.Modifier_run2_DT_2018_cff import run2_DT_2018
from Configuration.Eras.Modifier_run2_SiPixel_2018_cff import run2_SiPixel_2018
from Configuration.Eras.Modifier_run2_HLTconditions_2018_cff import run2_HLTconditions_2018
from Configuration.Eras.Modifier_run2_HLTconditions_2017_cff import run2_HLTconditions_2017
from Configuration.Eras.Modifier_run2_muon_2018_cff import run2_muon_2018
from Configuration.Eras.Modifier_run2_muon_2017_cff import run2_muon_2017
from Configuration.Eras.Modifier_run2_egamma_2018_cff import run2_egamma_2018
from Configuration.Eras.Modifier_run2_egamma_2017_cff import run2_egamma_2017
from Configuration.Eras.Modifier_run2_L1prefiring_cff import run2_L1prefiring
from Configuration.Eras.Modifier_ctpps_2017_cff import ctpps_2017
from Configuration.Eras.Modifier_ctpps_2018_cff import ctpps_2018
from Configuration.Eras.Modifier_run2_jme_2017_cff import run2_jme_2017

Run2_2018 = cms.ModifierChain(Run2_2017.copyAndExclude([run2_HEPlan1_2017, run2_muon_2017, run2_L1prefiring, run2_HLTconditions_2017, run2_egamma_2017, ctpps_2017, run2_jme_2017]),
run2_CSC_2018, run2_HCAL_2018, run2_HB_2018, run2_HE_2018,run2_DT_2018, run2_SiPixel_2018, 
run2_HLTconditions_2018, run2_muon_2018, run2_egamma_2018, ctpps_2018)