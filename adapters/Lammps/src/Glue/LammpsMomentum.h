/*
 *  LammpsMomentum.h
 *  API Glue
 *
 */

#ifndef LAMMPS_MOMENTUM_WRAPPER_H
#define LAMMPS_MOMENTUM_WRAPPER_H

namespace lammpswrappers
{

    class LammpsMomentum {
        public:
            LammpsMomentum(int steps, int type);
            void setState(bool state);
            bool getState();
            void setLinearFlags(int x, int y, int z);
            int getXLinearFlag();
            int getYLinearFlag();
            int getZLinearFlag();
            int getSteps();
            int getType();

            static const int LINEAR;
            static const int ANGULAR;

        private:
            bool enabled;
            int momentumSteps;
            int momentumType;
            bool xflag;
            bool yflag;
            bool zflag;

    };
}

#endif
