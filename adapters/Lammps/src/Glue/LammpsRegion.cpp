/*
 *  LammpsRegion.cpp
 *  API Glue
 *
 */

#include "atom.h"
#include "library.h"

#include "LammpsRegion.h"
#include "LammpsSpeciesSpheres.h"

namespace lammpswrappers
{

    LammpsRegion::LammpsRegion(IAPISimulation *sim) {
        char command[512];
        mSim = dynamic_cast<LammpsSimulation *>(sim);
        mSpecies = NULL;

        mRegionID = mSim->getRegionIDMgr()->getNextID();

    }

    /*
     * fillAtoms()
     */
    void LammpsRegion::fillAtoms(IAPISpecies *species) {
        if(species->getAtomTypeCount() == 1 &&
           typeid(*species) == typeid(LammpsSpeciesSpheres)) {
            mSpecies = species;
//        mSim->addRegionWithAtoms(this);

            char command[512];

            int preNatoms = (int)mSim->getLammpsSim()->atom->natoms;

            sprintf(command,
                    "create_atoms %d region %s",
                    mSpecies->getAtomType(0)->getIndex(),
                    mRegionID);
printf("lammps_command : %s\n", command); fflush(stdout);
            lammps_command(mSim->getLammpsSim(), command);

            int postNatoms = (int)mSim->getLammpsSim()->atom->natoms;

            for(int i = 0; i < postNatoms - preNatoms; i++) {
                IAPIMolecule *mole = dynamic_cast<LammpsSpeciesSpheres *>(mSpecies)->makeMolecule(mSim->getLammpsSim()->atom->tag[preNatoms+i]-1);
                mSim->getBox(0)->addMolecule(mole);
            }
        }
        else {
            printf("A region cannot be filled with multi-atomic molecules.\n"); fflush(stdout);
            printf("A region must be filled with a species derived from LammpsSpeciesSpheres.\n"); fflush(stdout);
        }

    }

    /*
     * getSpecies()
     */
    IAPISpecies *LammpsRegion::getSpecies() {
        return mSpecies;
    }

    /*
     * getRegionID()
     */
    char *LammpsRegion::getRegionID() {
        return mRegionID;
    }

}
