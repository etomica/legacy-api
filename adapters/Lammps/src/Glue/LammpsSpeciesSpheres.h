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
#include "LammpsInterfaceConformation.h"
#include "IAPISimulation.h"
#include "LammpsSpecies.h"
#include "LammpsAtomTypeSphere.h"
#include "LammpsNativeConformation.h"

using namespace molesimAPI;

namespace lammpswrappers
{

    class LammpsSpeciesSpheres : public LammpsSpecies, public virtual IAPISpecies {

        public:
            LammpsSpeciesSpheres(IAPISimulation *sim);
            LammpsSpeciesSpheres(IAPISimulation *sim, LammpsInterfaceConformation *conform);

            // API compliant methods
            IAPIMolecule *makeMolecule();

            // Non-API  methods
            void addChildType(IAPIAtomType *type, int nAtoms);
            IAPIMolecule *makeMolecule(int leafIndex);

    };
}

#endif
