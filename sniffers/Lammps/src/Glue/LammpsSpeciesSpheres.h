/*
 *  LammpsSpeciesSpheres.h
 *  API Glue
 *
 */

#ifndef LAMMPS_SPECIESSPHERES_WRAPPER_H
#define LAMMPS_SPECIESSPHERES_WRAPPER_H

#include <vector>

#include "IAPISpecies.h"
#include "IAPIAtomType.h"
#include "IAPIMolecule.h"
//#include "LammpsInterfaceConformation.h"
//#include "IAPISimulation.h"
#include "IAPISpeciesManager.h"
#include "LammpsSimulation.h"
#include "LammpsSpecies.h"
//#include "LammpsNativeConformation.h"

using namespace molesimAPI;

namespace lammpssnifferwrappers
{

    class LammpsSpeciesSpheres : public LammpsSpecies, public virtual IAPISpecies {

        public:
            LammpsSpeciesSpheres(LammpsSimulation *sim);
//            LammpsSpeciesSpheres(IAPISimulation *sim, LammpsInterfaceConformation *conform);

            // API compliant methods
            IAPIMolecule *makeMolecule();

            // Non-API  methods
            void addChildType(IAPIAtomType *type, int nAtoms);

    };
}

#endif
