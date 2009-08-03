/*
 *  LammpsRegionBlock.cpp
 *  API Glue
 *
 */

#include "library.h"

#include "LammpsRegionBlock.h"
#include "LammpsSimulation.h"

namespace lammpswrappers
{

    LammpsRegionBlock::LammpsRegionBlock(IAPISimulation *sim,
                                         IAPIVector *regionMin,
                                         IAPIVector *regionMax) : LammpsRegion(sim){
        char command[512];

        if(regionMin->getD() == 2) {
            sprintf(command,
                    "region %s block %f %f %f %f -0.5 0.5 units box",
                    mRegionID,
                    regionMin->getX(0),
                    regionMax->getX(0),
                    regionMin->getX(1),
                    regionMax->getX(1));
        }
        else {
            sprintf(command,
                    "region %s block %f %f %f %f %f %f units box",
                    mRegionID,
                    regionMin->getX(0),
                    regionMax->getX(0),
                    regionMin->getX(1),
                    regionMax->getX(1),
                    regionMin->getX(2),
                    regionMax->getX(2));
        }

printf("lammps_command : %s\n", command); fflush(stdout);
        lammps_command(mSim->getLammpsSim(), command);
        
    }

}
