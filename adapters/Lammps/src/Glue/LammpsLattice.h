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
            /**
              * Creates a lattice of the given type.
              * @param sim Simulation that contains the integrator.
              * @param sc Scale factor between lattice and simulation box.
              * @param name The name of the lattice
              */
            LammpsLattice(IAPISimulation *sim, double sc, const char *name);

            /**
              * Set the origin for the lattice for use in the native Lammps
              * lattice command.
              * @param vec Vector containing the origin location
              */
            void setOrigin(IAPIVector *vec);

        private:
            /**
              * Create a lattice of the type and with the parameters held
              * by this class instance.
              * Native Lammps calls :
              *   lattice
              */
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
