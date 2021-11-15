# Dimaond PPS Producer

### Configs:
* To run simulation step, use `step1_GEN_SIM` config file
* To run digitization step, use `step2_DIGI` config file


### How to run:
- cmsrel CMSSW_11_3_0_pre6
- cd CMSSW_11_3_0_pre6/src
- git clone https://github.com/mortezaPRK/NewDiamondProducer.git .
- cmsenv
- scram b
- cmsRun step1_GEN_SIM.py
- cmsRun step2_DIGI.py

