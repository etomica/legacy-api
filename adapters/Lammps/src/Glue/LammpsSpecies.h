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
#include "IAPIMolecule.h"
#include "LammpsInterfaceConformation.h"
#include "LammpsSimulation.h"

using namespace molesimAPI;


namespace lammpswrappers
{

    class LammpsSpecies : public virtual IAPISpecies {

        public:

            /**
              * Create a species.
              * @param sim Simulation that contains the species.
              * @param conform A conformation (see intitializeConformation)
              *                that will be used to set the position of
              *                atoms within the molecule.
              */
            LammpsSpecies(IAPISimulation *sim,
                          LammpsInterfaceConformation *conform);

            // API compliant methods
            int getIndex();
            void setIndex(int index);
            virtual IAPIMolecule *makeMolecule() = 0;
            virtual int getAtomTypeCount();
            virtual IAPIAtomType *getAtomType(int index);
            void initializeConformation(IAPIMolecule *molecule);

        protected:
            LammpsSimulation *mSim;
            LammpsInterfaceConformation *mConformation;
            std::vector<IAPIAtomType *> typeList;
            std::vector<int> typeCount;

        private:
            int mIndex;
    };
}

#endif
