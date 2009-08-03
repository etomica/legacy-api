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
            LammpsNVT(double tStart, double tStop, double tDamp, double dragVal);
            LammpsNVT(double tStart, double tStop, double tDamp, double dragVal, int DOF);
            double getStart();
            double getStop();
            double getDamp();
            double getDrag();
            bool useDOF();
            int getDOF();
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
