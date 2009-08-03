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
            LammpsNVE();
            char *getFixType();

        protected:
            char *fixType;
    };
}

#endif
