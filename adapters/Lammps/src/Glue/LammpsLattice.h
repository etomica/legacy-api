/*
 *  LammpsLattice.h
 *  API Glue
 *
 */

#ifndef LAMMPS_LATTICE_WRAPPER_H
#define LAMMPS_LATTICE_WRAPPER_H

#include "lammps.h"

#include "IAPISimulation.h"
#include "IAPIVector.h"
#include "IAPIVectorMutable.h"
#include "LammpsSimulation.h"

namespace lammpswrappers
{

    class LammpsLattice {

        public:
            LammpsLattice(IAPISimulation *sim, double sc, const char *name);

            void setOrigin(IAPIVector *vec);

        private:
            void lammpsSetup();
            LammpsSimulation *mSim;
            char *latticeName;
            double scale;
            bool originSet;
            IAPIVectorMutable *origin;
            bool orientSet;
            bool spacingSet;
            bool unitSet;
            bool basisSet;

    };
}

#endif
