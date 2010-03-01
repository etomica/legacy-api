/*
 *  LammpsInitialization.cpp
 *  API Glue
 *
 *
 */

#include "lammps.h"
#include "atom.h"

#include "LammpsAtom.h"
#include "LammpsAtomType.h"
#include "LammpsInitialization.h"
#include "LammpsMolecule.h"

namespace lammpssnifferwrappers
{


    LammpsInitialization::LammpsInitialization(LammpsSimulation *sim) {
        mSim = sim;
    }

    /*
     * init()
     */
    void LammpsInitialization::init() {
        initAtomTypes();

        if(strcmp(mSim->getLammpsSim()->atom->atom_style, "angle")     == 0 ||
           strcmp(mSim->getLammpsSim()->atom->atom_style, "bond")      == 0 ||
           strcmp(mSim->getLammpsSim()->atom->atom_style, "full")      == 0 ||
           strcmp(mSim->getLammpsSim()->atom->atom_style, "molecular") == 0) {

            initMoleculeData();
            initSpecieDataLevel0();
        }
        else {
            printf("ERROR : atom_style is not of the kind where a molecule can be created.\n");
        }

    }

    /*
     * getMolecules()
     */
    std::vector<LammpsMolecule *> LammpsInitialization::getMolecules() {
        return molecules;
    }

    /*
     * getSpecies()
     */
    std::vector<LammpsSpecies *> LammpsInitialization::getSpecies() {
        return species;
    }

    /*
     * initAtomTypes()
     */
    void LammpsInitialization::initAtomTypes() {

        LAMMPS *nativeSim = mSim->getLammpsSim();
        //
        // Create Atom Types
        //

        atomType = (LammpsAtomType **) malloc
           (nativeSim->atom->ntypes * sizeof(LammpsAtomType *));
printf("DEBUG : atom types -> %d\n", nativeSim->atom->ntypes);

        for(int i = 0; i < nativeSim->atom->natoms; i++) {
            bool inList = false;

            std::map<int, int>::iterator it;
            int idx = 0;
            for(it = atomTypeIndexToNativeIndex.begin(); it != atomTypeIndexToNativeIndex.end(); it++) {

                if(it->second == nativeSim->atom->type[i]) {
                    inList = true;
                    break;
                }
            }
            if(!inList) {
                atomTypeIndexToNativeIndex.insert(std::pair<int, int>(atomTypeIndexToNativeIndex.size(),
                   nativeSim->atom->type[i]));
            }
        }
printf("UNIQUE ATOM IDS FOUND(WHICH SHOULD MATCH ACTUAL NATIVE ATOM TYPES) : %d\n", atomTypeIndexToNativeIndex.size());

        std::map<int, int>::iterator it;
        int idx = 0;
        for(it = atomTypeIndexToNativeIndex.begin(); it != atomTypeIndexToNativeIndex.end(); it++) {

            atomType[idx] = new LammpsAtomType(it->first, it->second, nativeSim->atom->mass[it->first+1]);
            atomType[idx]->setIndex(idx);
            nativeIndexToAtomType.insert(std::pair<int, LammpsAtomType *>(it->second, atomType[idx++]));
        }

    }

    /*
     * initMoleculeData()
     */
    void LammpsInitialization::initMoleculeData() {

        LAMMPS *nativeSim = mSim->getLammpsSim();

        moleculeCount = 0;


printf("WARNING : The code just below this is checking the molecule flag and may not be using the corret index to do so!  Check this code\n");

        for(int atomIdx = 0; atomIdx < (long)nativeSim->atom->natoms; atomIdx++) {

            // monatomic molecule may have molecule id of 0
            if(nativeSim->atom->molecule[atomIdx] == 0) {


                LammpsMolecule *mole = new LammpsMolecule(nativeSim->atom->molecule[atomIdx]);

                LammpsAtom *a = new LammpsAtom(mSim,
                   nativeIndexToAtomType[nativeSim->atom->type[atomIdx]], mole, atomIdx);
                a->setIndex(mole->getChildList()->getAtomCount());

                mole->addChildAtom(a);

                molecules.push_back(mole);
                moleculeCount++;

            }
            else {
                LammpsMolecule *mole = NULL;

                bool moleExists = false;
                for(int i = 0; i < molecules.size(); i++) {
                    if(molecules.at(i)->getNativeIndex() == nativeSim->atom->molecule[atomIdx]) {
                        moleExists = true;
                        mole = molecules.at(i);
                        break;
                    }
                }

                if(!moleExists) {
                    mole = new LammpsMolecule(nativeSim->atom->molecule[atomIdx]);
                    molecules.push_back(mole);
                    moleculeCount++;
                }
                LammpsAtom *a = new LammpsAtom(mSim,
                   nativeIndexToAtomType[nativeSim->atom->type[atomIdx]], mole, atomIdx);
                a->setIndex(mole->getChildList()->getAtomCount());

                mole->addChildAtom(a);

            }
        }

    }

    /*
     * initSpecieDataLevel0()
     */
    void LammpsInitialization::initSpecieDataLevel0() {

        // Create a species for the first molecule in the list.
        LammpsMolecule *mole = molecules.at(0);
        std::vector<LammpsAtomType *>atomTypeList;
        // Get an atom type list
        for(int i = 0; i < mole->getChildList()->getAtomCount(); i++) {
            atomTypeList.push_back(
               dynamic_cast<LammpsAtomType *>(mole->getChildList()->getAtom(i)->getType()));
        }
        // Create species passing atom types in ctor
        LammpsSpecies *newSpecie = new LammpsSpecies(mSim, atomTypeList);

        species.push_back(newSpecie);
        mole->setSpecies(newSpecie);

        for(int i = 0; i < mole->getChildList()->getAtomCount(); i++) {
            mole->getChildList()->getAtom(i)->getType()->setSpecies(newSpecie);
        }

        // Parse thru all molecules and pull out each unique one
        // and make a specie from it
        for(int moleIdx = 1; moleIdx < molecules.size(); moleIdx++) {

            mole = molecules.at(moleIdx);

            // Either all of the atoms in the list have the
            // same atom type (or no atom type) or there
            // is an input error
            for(int atIdx = 1; atIdx < mole->getChildList()->getAtomCount(); atIdx++) {
                if(mole->getChildList()->getAtom(atIdx)->getType()->getSpecies() !=
                   mole->getChildList()->getAtom(atIdx - 1)->getType()->getSpecies()) {
printf("ERROR : Molecule has atoms with types of different species and this is catastrophic!\n");
                    return;
                }
            }
            // molecule has atoms with types of all the same species
            // (or no species).  If the species is not assigned, assign one
            if(mole->getChildList()->getAtom(0)->getType()->getSpecies() == NULL) {

                // Get an atom type list
                std::vector<LammpsAtomType *>atomTypeList;
                for(int i = 0; i < mole->getChildList()->getAtomCount(); i++) {
                    atomTypeList.push_back(dynamic_cast<LammpsAtomType *>(mole->getChildList()->getAtom(i)->getType()));
                }
                // Create species passing atom types in ctor
                newSpecie = new LammpsSpecies(mSim, atomTypeList);

                species.push_back(newSpecie);

            }

            mole->setSpecies(newSpecie);

            for(int i = 0; i < mole->getChildList()->getAtomCount(); i++) {
                mole->getChildList()->getAtom(i)->getType()->setSpecies(newSpecie);
            }

        }

    }


}
