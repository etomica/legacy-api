/*
 *  LammpsNPT.h
 *  API Glue
 *
 */

#ifndef LAMMPS_NPT_WRAPPER_H
#define LAMMPS_NPT_WRAPPER_H

namespace lammpswrappers
{

    class LammpsNPT {
        public:
            /**
              * Class that stores parameters for the native Lammps
              * simulation npt fix.
              * @param tStart Temperature at start of simulation.
              * @param tStop Temperature at end of simulation.
              * @param tDamp Temperature damping parameter.
              */
            LammpsNPT(double tStart, double tStop, double tDamp);

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
              * @return Returns the fix type
              */
            char *getFixType();

        protected:
            char *fixType;
            double start;
            double stop;
            double damp;
    };
}

#endif
