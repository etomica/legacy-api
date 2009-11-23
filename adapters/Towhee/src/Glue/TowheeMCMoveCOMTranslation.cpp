/*
 *  TowheeMCMoveCOMTranslation.cpp
 *  API Glue
 *
 *
 */

#include "stdio.h"
#if defined(__MACH__) && defined(__APPLE__)
#include "stdlib.h"
#else
#include "malloc.h"
#endif

#include "preproc.h"

#include "TowheeMCMoveCOMTranslation.h"

extern "C" { void twh_pmtracm_(int *, double *); }
extern "C" { void twh_pmtcmt_(int *, int *, double *); }
extern "C" { void twh_rmtrac_(int *, int *, int *, double *); }
extern "C" { void twh_tatrac_(int *, double *); }
extern "C" { void twh_numboxes_(int *, int *); }

namespace towheewrappers
{

    TowheeMCMoveCOMTranslation::TowheeMCMoveCOMTranslation(IAPISimulation *sim, double p) :
                                   TowheeMCMove(p) {
        mSimulation = sim;
    }

    /*
     * setPmtcmt()
     */
    void TowheeMCMoveCOMTranslation::setPmtcmt(double values[]) {
        pmtcmt = (double *) malloc (mSimulation->getSpeciesCount() * sizeof(double));
        for(int i = 0; i < mSimulation->getSpeciesCount(); i++)
            pmtcmt[i] = values[i];
    }

    /*
     * setRmtrac()
     */
    void TowheeMCMoveCOMTranslation::setRmtrac(double value) {
        rmtrac = value;
    }

    /*
     * setTatrac()
     */
    void TowheeMCMoveCOMTranslation::setTatrac(double value) {
        tatrac = value;
    }


    /*
     * setup()
     */
    void TowheeMCMoveCOMTranslation::setup() {
printf("WARNING : TowheeMCMoveCOMTranslation::setup() is not implemented yet.\n"); fflush(stdout);
        int set = GLB_SET;

// This is the cumulutive probability and as such, probably needs to be managed
// by the IntegratorMC to get the current cumulutive number
        // Set probability of this move type (pmtracm)
        twh_pmtracm_(&set, &probability);

        double probMax = 0.0;
        double value;
        for(int i = 1; i <= mSimulation->getSpeciesCount(); i++) {
            value = pmtcmt[i-1];
            twh_pmtcmt_(&set, &i, &value);
            if (value > probMax ) probMax = value;
        }

        if(probMax < 1.0) {
            printf("ERROR : At least one value of pmtcmt must be 1.0\n");
            return;
        }

        if (value <= 0.0) {
            printf("ERROR : rmtrac must be > 0\n");
            return;
        }

        int numBoxes;
        int get = GLB_GET;
//        twh_numboxes_(&get, &numBoxes);
numBoxes = 1;
printf("TowheeMCMoveCOMTranslation HARDCODED num boxes : %d\n", numBoxes); fflush(stdout);

        for(int ibox = 1; ibox <= numBoxes; ibox++) {
            for(int i = 1; i <= mSimulation->getSpeciesCount(); i++) {
                twh_rmtrac_(&set, &i, &ibox, &rmtrac);
            }
        }

        // The target acceptance rate for the center-of-mass translation move.
        // Must be a value between 0.0 and 1.0. (tatrac)
        twh_tatrac_(&set, &tatrac);

        if (tatrac <= 0.0 || tatrac >= 1.0) {
            printf("ERROR : tatrac must be between 0.0 and 1.0\n");
            return;
        }

    }

}
