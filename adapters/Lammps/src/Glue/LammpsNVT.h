/*
 *  LammpsNVT.h
 *  API Glue
 *
 */

#ifndef LAMMPS_NVT_WRAPPER_H
#define LAMMPS_NVT_WRAPPER_H

namespace lammpswrappers
{

    class LammpsNVT {

        public:
            /**
              * Class that stores parameters for the native Lammps
              * simulation nvt fix.
              * @param tStart Temperature at start of simulation.
              * @param tStop Temperature at end of simulation.
              * @param tDamp Temperature damping parameter.
              * @param drag factor added to thermostat
              */
            LammpsNVT(double tStart, double tStop, double tDamp, double dragVal);
            /**
              * Class that stores parameters for the native Lammps
              * simulation nvt fix.
              * @param tStart Temperature at start of simulation.
              * @param tStop Temperature at end of simulation.
              * @param tDamp Temperature damping parameter.
              * @param drag factor added to thermostat
              * @param DOF Number of extra degrees of freedom to subtract.
              */
            LammpsNVT(double tStart, double tStop, double tDamp, double dragVal, int DOF);
            /**
              * @return Returns the temperature at start of simulation.
              */
            double getStart();
            /**
              * @return Returns the temperature at end of simulation.
              */
            double getStop();
            /**
              * @return Returns the temperature damping parameter.
              */
            double getDamp();
            /**
              * @return Returns the drag factor parameter.
              */
            double getDrag();
            /**
              * @return Returns the flag indicating whether to use
              *         the native Lammps simulation compute_modify ... extra
              *         command.
              */
            bool useDOF();
            /**
              * @return Returns the degrees of freedom parameter.
              */
            int getDOF();
            /**
              * @return Returns the fix type.
              */
            char *getFixType();
 
        protected:
            char *fixType;
            double start;
            double stop;
            double damp;
            double drag;
            bool dofUsage;
            int dof;
    };
}

#endif
