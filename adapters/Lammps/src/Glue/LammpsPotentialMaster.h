/*
 *  LammpsPotentialMaster.h
 *  API Glue
 *
 */

#ifndef LAMMPS_POTENTIAL_MASTER_WRAPPER_H
#define LAMMPS_POTENTIAL_MASTER_WRAPPER_H

#include <vector>

#include "IAPIBox.h"
#include "IAPIAtomType.h"
#include "IAPIPotential.h"
#include "IAPIPotentialAtomic.h"
#include "IAPISimulation.h"
#include "IAPISpecies.h"
#include "LammpsSimulation.h"

using namespace molesimAPI;

namespace lammpswrappers
{

    class LammpsPotentialMaster {

        public:			

            LammpsPotentialMaster(IAPISimulation *sim);

            // API Compliance
            void addPotential(IAPIPotentialAtomic *potential, IAPIAtomType *at1, IAPIAtomType *at2);

            // Non-API Method
            // The next method is very close to the API method :
            //  addPotential(IPotential, ISpecies[]);
            void addPotential(IAPIPotential *potential, IAPISpecies *species);
            void lammpsSetup(IAPIBox *box);
            int getTotalBondCount();
            int getPairTypeCount(IAPIBox *box);

        private:
            int setBondStyle(IAPIBox *box);
            int setPairStyle(IAPIBox *box);
            int getBondTypeCount();

            LammpsSimulation *mSim;
            // Bond List info
            std::vector<IAPIPotential *> bondPotentialList;
            std::vector<IAPISpecies *> speciesList;
            // Pair List info
            std::vector<IAPIPotential *> pairPotentialList;
    };
}
#endif
