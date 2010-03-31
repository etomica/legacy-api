/*
 *  LammpsNVE.h
 *  API Glue
 *
 */

#ifndef LAMMPS_NVE_WRAPPER_H
#define LAMMPS_NVE_WRAPPER_H

namespace lammpswrappers
{

    class LammpsNVE {
        public:
            /**
              * Class that stores parameters for the native Lammps
              * simulation nve fix.
              */
            LammpsNVE();
            /**
              * @return Returns the fix type
              */
            char *getFixType();

        protected:
            char *fixType;
    };
}

#endif
