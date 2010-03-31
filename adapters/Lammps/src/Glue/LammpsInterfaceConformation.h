/*
 *  LammpsInterfaceConformation.h
 *  API Glue
 *
 */

#ifndef LAMMPS_ICONFORMATION_WRAPPER_H
#define LAMMPS_ICONFORMATION_WRAPPER_H

#include "IAPIAtomList.h"

using namespace molesimAPI;

namespace lammpswrappers
{


    class LammpsInterfaceConformation {

        public:
            /**
              * Sets the position of atoms(probably in the same molecule).
              * The atoms will probably already have a position and this
              * method will adjust the positions to reflect their position
              * within a the given list(molecule).
              * @param atom A list containing atoms
              */
            virtual void initializePositions(IAPIAtomList *atom) = 0;
    };
}
#endif
