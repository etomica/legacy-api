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
            LammpsNPT(double tStart, double tStop, double tDamp);
            double getStart();
            double getStop();
            double getDamp();
            char *getFixType();

        protected:
            char *fixType;
            double start;
            double stop;
            double damp;
    };
}

#endif
