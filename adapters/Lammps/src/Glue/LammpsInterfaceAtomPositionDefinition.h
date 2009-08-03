/*
 *  LammpsInterfaceAtomPositionDefinition.h
 *  API Glue
 *
 */

#ifndef LAMMPS_IATOMPOSITIONDEF_WRAPPER_H
#define LAMMPS_IATOMPOSITIONDEF_WRAPPER_H

#include "IAPIVector.h"
#include "IAPIMolecule.h"

using namespace molesimAPI;

namespace lammpswrappers
{

    class LammpsInterfaceAtomPositionDefinition {

        public:
            virtual IAPIVector *position(IAPIMolecule *atom) = 0;
    };
}
#endif
