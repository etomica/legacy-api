/*
 *  LammpsConformation.cpp
 *  API Glue
 *
 */

#include "stdio.h"
#include <math.h>

#include "IAPIVector.h"
#include "LammpsConformation.h"
#include "LammpsAtom.h"

namespace lammpssnifferwrappers
{

    LammpsConformation::LammpsConformation(IAPISimulation *sim) {
        mSim = dynamic_cast<LammpsSimulation *>(sim);
    }

    /*
     * initializePositions()
     */
    void LammpsConformation::initializePositions(IAPIAtomList *as) {
        printf("LammpsConformation::initializePositions(IAPIAtomList *) not implemented.\n");
    }

}
