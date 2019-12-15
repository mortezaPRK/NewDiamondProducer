## Release CMS

```shell
cmsrel CMSSW_11_1_X_2019-12-06-2300
```

## Clone this repo

```shell
cd CMSSW_11_1_X_2019-12-06-2300/src
git clone <CURRENT_URL> .
```


## Build and Run

```shell
cmsenv
scram b -j10
cmsRun gluglu_step1_GEN_SIM_2017.py
cmsRun gluglu_step2_DIGI_DIGI2RAW_2017.py
```