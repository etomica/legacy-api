/*
 *  LammpsRegionSphere.cpp
 *  API Glue
 *
 */

#include "library.h"

#include "LammpsRegionSphere.h"
#include "LammpsSimulation.h"

namespace lammpswrappers
{

    LammpsRegionSphere::LammpsRegionSphere(IAPISimulation *sim,
                                           IAPIVector *center,
                                           double radius) : LammpsRegion(sim){
        char command[512];

        if(center->getD() == 2) {
            sprintf(command,
                    "region %s sphere %f %f 0.5 %f units box",
                    mRegionID,
                    center->getX(0),
                    center->getX(1),
                    radius);
        }
        else {
            sprintf(command,
                    "region %s sphere %f %f %f %f units box",
                    mRegionID,
                    center->getX(0),
                    center->getX(1),
                    center->getX(2),
                    radius);
        }

printf("lammps_command : %s\n", command); fflush(stdout);
        lammps_command(mSim->getLammpsSim(), command);
        
    }

}
