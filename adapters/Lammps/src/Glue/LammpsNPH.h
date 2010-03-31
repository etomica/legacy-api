/*
 *  LammpsNPH.h
 *  API Glue
 *
 */

#ifndef LAMMPS_NPH_WRAPPER_H
#define LAMMPS_NPH_WRAPPER_H

namespace lammpswrappers
{

    class LammpsNPH {

        public:
            /**
              * Class that stores parameters for the native Lammps
              * simulation nph fix.
              */
            LammpsNPH();
            /**
              * @return Returns the fix type.
              */
            char *getFixType();

        protected:
            char *fixType;

    };
}

#endif
