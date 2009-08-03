/*
 *  LammpsRegionPrism.cpp
 *  API Glue
 *
 */

#include "library.h"

#include "LammpsRegionPrism.h"
#include "LammpsSimulation.h"

namespace lammpswrappers
{

    LammpsRegionPrism::LammpsRegionPrism(IAPISimulation *sim,
                                         IAPIVector *min,
                                         IAPIVector *max,
                                         double xy, double xz, double yz) : LammpsRegion(sim){
        char command[512];

        if(min->getD() == 2) {
            sprintf(command,
                    "region %s prism %f %f %f %f -0.5 0.5 %f 0.0 0.0 units box",
                    mRegionID,
                    min->getX(0),
                    max->getX(0),
                    min->getX(1),
                    max->getX(1),
                    xy);
        }
        else {
            sprintf(command,
                    "region %s prism %f %f %f %f %f %f %f %f %f units box",
                    mRegionID,
                    min->getX(0),
                    max->getX(0),
                    min->getX(1),
                    max->getX(1),
                    min->getX(2),
                    max->getX(2),
                    xy, xz, yz);
        }

printf("lammps_command : %s\n", command); fflush(stdout);
        lammps_command(mSim->getLammpsSim(), command);
        
    }

}
