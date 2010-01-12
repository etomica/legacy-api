/*
 *  LammpsSpeciesSpheresSpheres.cpp
 *  API Glue
 *
 */

#include "stdio.h"

#include "atom.h"
#include "atom_vec.h"
#include "library.h"
#include <map>

#include "LammpsSpeciesSpheres.h"
#include "LammpsAtom.h"
#include "LammpsMolecule.h"
//#include "LammpsConformation.h"


namespace lammpssnifferwrappers
{

    LammpsSpeciesSpheres::LammpsSpeciesSpheres(LammpsSimulation *sim) : LammpsSpecies(sim) {
    }

//    LammpsSpeciesSpheres::LammpsSpeciesSpheres(
//                               IAPISimulation *sim,
//                               LammpsInterfaceConformation *conform) : LammpsSpecies(sim, conform) {
//    }

    /*
     * makeMolecule()
     */
    IAPIMolecule *LammpsSpeciesSpheres::makeMolecule() {

        LammpsMolecule *mole = new LammpsMolecule();
        std::map<IAPIAtomType *, int>::iterator it;
printf("DEBUG : typelist size : %d\n", typeList.size()); fflush(stdout);
        for(int i = 0; i < typeList.size(); i++) {
            for(int j = 0; j < typeCount.at(i); j++) {
printf("  creating atom...\n"); fflush(stdout);
                IAPIAtom *atom = new LammpsAtom(mSim, typeList.at(i));
printf("  ...atom created\n"); fflush(stdout);
                mole->addChildAtom(atom);
printf("added atom to molecule\n"); fflush(stdout);
                atom->setIndex(j);
            }
        }

        return mole;
    }

    /*
     * addChildType()
     */
    void LammpsSpeciesSpheres::addChildType(IAPIAtomType *type, int nAtoms) {

        type->setSpecies(this);
        typeList.push_back(type);
        typeCount.push_back(nAtoms);
    }

    /*
     * makeMolecule() - Non-API
     */
    IAPIMolecule *LammpsSpeciesSpheres::makeMolecule(int leafIndex) {

        LammpsMolecule *mole = NULL;

        if(getAtomTypeCount() == 1 && typeCount.at(0) == 1) {
            mole = new LammpsMolecule();
            IAPIAtom *atom = new LammpsAtom(mSim, typeList.at(0));
            mole->addChildAtom(atom);
            atom->setIndex(0);
        }
        else {
            printf("Cannot create a molecule in this manner that is multi-atomic.\n"); fflush(stdout);
        }

        return mole;
    }

}
