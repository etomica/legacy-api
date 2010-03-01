/*
 *  LammpsInitialization.h
 *  API Glue
 *
 */

#ifndef LAMMPS_INIT_WRAPPER_H
#define LAMMPS_INIT_WRAPPER_H

#include <map>
#include <vector>

#include "LammpsAtomType.h"
#include "LammpsMolecule.h"
#include "LammpsSimulation.h"
#include "LammpsSpecies.h"

using namespace molesimAPI;

namespace lammpssnifferwrappers
{

    class LammpsInitialization {

        public:
            LammpsInitialization(LammpsSimulation *sim);
            void init();
            std::vector<LammpsMolecule *>getMolecules();
            std::vector<LammpsSpecies *>getSpecies();

        private:
            void initAtomTypes();
            void initMoleculeData();
            void initSpecieDataLevel0();

            LammpsSimulation *mSim;
            LammpsAtomType **atomType;
            int moleculeCount;

            std::map<int, int> atomTypeIndexToNativeIndex; // glue layer index, native type index
            std::map<int, LammpsAtomType *> nativeIndexToAtomType; // native type index, LammpsAtomType
            std::vector<LammpsMolecule *> molecules;
            std::vector<LammpsSpecies *> species;
    };


}

#endif
