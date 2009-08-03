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
            LammpsNPH();
            char *getFixType();

        protected:
            char *fixType;

    };
}

#endif
