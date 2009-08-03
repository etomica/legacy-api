/*
 *  LammpsLattice.cpp
 *  API Glue
 *
 */

#include "library.h"

#include "LammpsLattice.h"

namespace lammpswrappers
{

    LammpsLattice::LammpsLattice(IAPISimulation *sim, double sc, const char *name) {
        mSim = dynamic_cast<LammpsSimulation *>(sim);
        scale = sc;
        latticeName = (char *)malloc ((strlen(name) + 1) * sizeof(char));
        strcpy(latticeName, name);
        originSet = false;
        orientSet = false;
        spacingSet = false;
        unitSet = false;
        basisSet = false;

        lammpsSetup();
    }

    /*
     *
     */
    void LammpsLattice::setOrigin(IAPIVector *vec) {
        origin = mSim->getSpace()->makeVector();
        origin->E(vec);
        originSet = true;
        lammpsSetup();
    }

    /*
     * lammpsSetup()
     */
    void LammpsLattice::lammpsSetup() {

        char command[512];

        // In case lattice previously set, unset it so that new
        // lattice can be used.
        sprintf(command,
               "lattice none");

printf("lammps_command : %s\n", command); fflush(stdout);
        lammps_command(mSim->getLammpsSim(), command);

        sprintf(command,
               "lattice %s %f",
               latticeName,
               scale);

        if(originSet) {
            if(origin->getD() == 2) {
                sprintf(command,
                        "%s origin %f %f 0.0",
                        command,
                        origin->getX(0),
                        origin->getX(1));
            }
            else {
                sprintf(command,
                        "%s origin %f %f %f",
                        command,
                        origin->getX(0),
                        origin->getX(1),
                        origin->getX(2));
            }
        }

        if(orientSet) {
        }

        if(spacingSet) {
        }

        if(unitSet) {
        }

        if(basisSet) {
        }

printf("lammps_command : %s\n", command); fflush(stdout);
        lammps_command(mSim->getLammpsSim(), command);

    }

}
