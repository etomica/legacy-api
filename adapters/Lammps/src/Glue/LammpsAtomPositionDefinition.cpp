/*
 *  LammpsAtomPositionDefinition.cpp
 *  API Glue
 *
 */

#include "stdio.h"

#include "IAPIAtom.h"
#include "IAPIVector.h"
#include "LammpsAtomPositionDefinition.h"

namespace lammpswrappers
{

    /*
     * position()
     */
    IAPIVector *LammpsAtomPositionDefinition::position(IAPIMolecule *atom) {
        printf("WARNING : LammpsAtomPositionDefinition::position is NOT implemented yet.\n");
    }

}
