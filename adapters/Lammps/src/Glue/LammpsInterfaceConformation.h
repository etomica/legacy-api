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
            virtual void initializePositions(IAPIAtomList *) = 0;
    };
}
#endif
