/*
 *  LammpsAtomPositionDefinition.h
 *  API Glue
 *
 */

#ifndef LAMMPS_ATOMPOSDEF_WRAPPER_H
#define LAMMPS_ATOMPOSDEF_WRAPPER_H

#include "IAPIMolecule.h"
#include "LammpsInterfaceAtomPositionDefinition.h"
#include "IAPIVector.h"

using namespace molesimAPI;

namespace lammpswrappers
{

    class LammpsAtomPositionDefinition : public virtual LammpsInterfaceAtomPositionDefinition {

        public:			

            // API Compliance
            /**
              * This method is not implemented.
              */
            IAPIVector *position(IAPIMolecule *atom);

    };
}
#endif
