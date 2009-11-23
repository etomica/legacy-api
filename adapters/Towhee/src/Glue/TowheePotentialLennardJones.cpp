/*
 *  TowheePotentialLennardJones.cpp
 *  API Glue
 *
 */

#include "stdio.h"
#include "string.h"

#include "preproc.h"

#include "TowheePotentialLennardJones.h"

extern "C" { void twh_classical_potential_c_(int *, char *, int *); }
extern "C" { void twh_classical_mixrule_c_(int *, char *, int *); }
extern "C" { void twh_lshift_(int *, int *); }
extern "C" { void twh_ltailc_(int *, int *); }
extern "C" { void twh_rmin_(int *, double *); }
extern "C" { void twh_rcut_(int *, double *); }
extern "C" { void twh_rcutin_(int *, double *); }

namespace towheewrappers
{

    const int TowheePotentialLennardJones::LORENTZ_BERTHELOT = 0;
    const int TowheePotentialLennardJones::GEOMETRIC = 1;
    const int TowheePotentialLennardJones::EXPLICIT = 2;
    const int TowheePotentialLennardJones::SHUKLA = 3;

    TowheePotentialLennardJones::TowheePotentialLennardJones() {
        mMixRule = LORENTZ_BERTHELOT;
        mLShift = false;
        mTailc = true;
        mRMin = 0.5;
        mRCut = 2.5;
        mRCutin = 1.0;
    }

    /*
     * energy()
     */
    double TowheePotentialLennardJones::energy(IAPIAtomList *atomList) {
    }

    /*
     * setClassicalMixRule()
     */
    void TowheePotentialLennardJones::setClassicalMixRule(int mixRule) {
        mMixRule = mixRule;
    }

    /*
     * setup()
     */
    void TowheePotentialLennardJones::setup() {
        int set = GLB_SET;

        char potStyle[30] = "Lennard-Jones";
        int len = strlen(potStyle);
        twh_classical_potential_c_(&set, potStyle, &len);

        char *mixRules[] = { "Lorentz-Berthelot", "Geometric",
                             "Explicit", "Shukla" };
        char mixrule[30];
        strcpy(mixrule, mixRules[mMixRule]);
        len = strlen(mixrule);
        twh_classical_mixrule_c_(&set, mixrule, &len);

        int lValue = 0;
        if(mLShift) lValue = 1;
        twh_lshift_(&set, &lValue);
        lValue = 0;
        if(mTailc) lValue = 1;
        twh_ltailc_(&set, &lValue);
        twh_rmin_(&set, &mRMin);
        twh_rcut_(&set, &mRCut);
        twh_rcutin_(&set, &mRCutin);

    }

}
