/*
 *  GlotzillaInterfaceConformation.h
 *  API Glue
 *
 */

#ifndef GLOTZ_ICONFORMATION_WRAPPER_H
#define GLOTZ_ICONFORMATION_WRAPPER_H

#include "IAPIAtomList.h"

using namespace molesimAPI;

namespace glotzwrappers
{


    class GlotzillaInterfaceConformation {

        public:
            /**
              * Sets the position of atoms(probably in the same molecule).
              * The atoms will probably already have a position and this
              * method will adjust the positions to reflect their position
              * within a the given list(molecule).
              * @param atom An list containing atoms
              */
            virtual void initializePositions(IAPIAtomList *atom) = 0;
    };
}
#endif
