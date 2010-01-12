/*
 *  LammpsSpecies.h
 *  API Glue
 *
 */

#ifndef LAMMPS_SPECIES_WRAPPER_H
#define LAMMPS_SPECIES_WRAPPER_H

#include <vector>

#include "IAPISpecies.h"
#include "IAPIAtomType.h"
#include "IAPISpeciesManager.h"
#include "IAPIMolecule.h"
//#include "LammpsInterfaceConformation.h"
#include "LammpsSimulation.h"

using namespace molesimAPI;


namespace lammpssnifferwrappers
{

    class LammpsSpecies : public virtual IAPISpecies {

        public:

//            LammpsSpecies(IAPISimulation *sim,
//                          LammpsInterfaceConformation *conform);
            LammpsSpecies(LammpsSimulation *sim);

            // API compliant methods
            int getIndex();
            void setIndex(int index);
            virtual IAPIMolecule *makeMolecule() = 0;
            virtual int getAtomTypeCount();
            virtual IAPIAtomType *getAtomType(int index);
            void initializeConformation(IAPIMolecule *molecule);

        protected:
            LammpsSimulation *mSim;
//            LammpsInterfaceConformation *mConformation;
            std::vector<IAPIAtomType *> typeList;
            std::vector<int> typeCount;

        private:
            int mIndex;
    };
}

#endif
