/*
 *  TowheeBasicConnectivityMap.cpp
 *  API Glue
 *
 *
 */

#include "stdio.h"
#include "string.h"

#include "preproc.h"

#include "TowheeBasicConnectivityMap.h"

extern "C" { void twh_nunit_(int *, int *, int *); }
extern "C" { void twh_nmaxcbmc_(int *, int *, int *); }
extern "C" { void twh_charge_assignment_c_(int *, int *, char *, int *); }
extern "C" { void twh_qqatom_(int *, int *, int *, double *); }
extern "C" { void twh_invib_(int *, int *, int *, int *); }
extern "C" { void twh_assemble_(int *, int *, int *, int *, char *, char *, char *, char *, int *); }

namespace towheewrappers
{

    TowheeBasicConnectivityMap::TowheeBasicConnectivityMap() {
    }

    void TowheeBasicConnectivityMap::setup(IAPIMolecule *molecule, TowheeForceField *ff) {

        // Assumming lpdbnames is false
        // Charge assignment is 'manual'
        // Charge of all atoms is 0
        // Vibration of all atoms is 0

        int set = GLB_SET;
        int zero = 0;
        double zeroPtZero = 0.0;
        int True = 1;
        char *blankString = "";

        IAPIAtomList *atomList = molecule->getChildList();

        int numAtoms = atomList->getAtomCount();
        int speciesIdx = molecule->getType()->getIndex() + 1;

        // nunit
        twh_nunit_(&set, &speciesIdx, &numAtoms);

        // nmaxcbmc
        twh_nmaxcbmc_(&set, &speciesIdx, &numAtoms);

        // forcefield
//'LJium'

        // charge_assignment
        char cAssign[10] = "manual";
        int len = strlen(cAssign);
        twh_charge_assignment_c_(&set, &speciesIdx, cAssign, &len);

        // stuff done in twh_buildmolec

        // unit ntype qqatom
        for(int i = 1; i <= numAtoms; i++) {
//            twh_ntype_(&set, &speciesIdx, &i, &);
            twh_qqatom_(&set, &speciesIdx, &i, &zeroPtZero);
        }

        // would set pdb names here if applicable (set to false above)

        // vibration (set to zero for now)
        for(int i = 1; i <= numAtoms; i++) {
            twh_invib_(&set, &speciesIdx, &i, &zero);
        }

        int failFlag = 0;
//        twh_assemble_(&failFlag, &speciesIdx, &numAtoms, &zero,
//                      ff->getForcefieldName(), <atom name>,
//                      &blankString, &blankString, &True);



    }

}
