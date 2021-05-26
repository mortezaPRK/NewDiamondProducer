----
How to Develop:

- cmsrel CMSSW_11_3_0_pre6
- cd CMSSW_11_3_0_pre6
- git clone <git url> src
- cd src
- cmsenv
- scram b -j10
- run `cmsRun step1_GEN_SIM.py` to run simulation
- run `cmsRun step2_DIGI.py` to run digitization

----
Digi Flow:

-> `DiamondDigiProducer::produce`
    // main module function
    -> `DiamondDetDigitizer::run`
        // input is a vector<psimhit>
        // output is void
        // loops over every hit in vector<psimhit> and calls `processHit` for
        //  each hit.
        -> `RDimHitChargeConverter::processHit`
            // input is psimhit
            // output is Map<ChargeByPart>
            // converts every `psimhit` to a Map<int, double>
            // what is map<?, ?>
            -> `RDimLinearChargeDivider::divide`
                // input is psimhit
                // output is vector<RDimEnergyDepositUnit>
                // evaluates energy loss the hit
                // divides energy of hit to 20 segments
            -> `RDimLinearChargeCollectionDrifter::Drift`
                // input is vector<RDimEnergyDepositUnit>
                // output is vector<RDimSignalPoint>
                // converts energy of each `RDimEnergyDepositUnit` to
                //  electron charge
                // sigma is constant value
            -> `RDimChargeShare::Share`
                // input is vector<RDimSignalPoint>
                // output is Map<ChargeByPart>
                // assigns effective charge from each `RDimSignalPoint` to
                //  a detector segement. segements are labled from 1 to 8
                // output is Map<detector segement lable, effective induced charge>
                // this is where we are using our topology
        -> `RDimPileUpSignals::dumpSignal` && `RDimPileUpSignals::dumpLinks`
            // Sum of all Map<ChargeByPart> for all vector<psimhit>
            // `dumpSignal` returns the sum of all Map<ChargeByPart>
            // `dumpLinks` returns an empty map<unsigned short,vector<pair<int, double>>> (!)
    -> `RDimDummyROCSimulator::ConvertChargeToHits`
        // converts `ChargeByPart` to Digi

---
`RDimEnergyDepositUnit`: holds 3d position (exit point) and energy
`RDimSignalPoint`: holds sigma, charge and 2d local position
`ChargeByPart` : <unsigned short, double>

