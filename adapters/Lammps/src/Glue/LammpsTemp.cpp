/*
 *  LammpsTemp.cpp
 *  API Glue
 *
 */

#include "library.h"
#include "modify.h"

#include "LammpsTemp.h"

namespace lammpswrappers
{

    LammpsTemp::LammpsTemp(LammpsSimulation *sim) {
        // Create a simulation
        Modify *modify = sim->getLammpsSim()->modify;

        printf("NUMBER OF COMPUTES : %d\n", modify->ncompute); fflush(stdout);

    }

}
