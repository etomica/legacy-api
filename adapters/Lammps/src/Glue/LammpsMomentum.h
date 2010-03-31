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
            /**
              * Create a momentum object and store momentum parameters for
              * use in native Lammps simulation fix ... momentum command.
              * @param steps Adjust the momentum every this many timesteps.
              * @param type keyword to the native Lammps simulation momentum
              *             fix command. Possible values :
              *   LINEAR  = 0
              *   ANGULAR = 1
              */
            LammpsMomentum(int steps, int type);

            /**
              * @param state Indicate if the momentum is enabled or disabled.
              */
            void setState(bool state);
            /**
              * @return Returns enabled/disabled state of momentum.
              */
            bool getState();
            /**
              * Set the include/exclude momentum fix for each dimension.
              * @param x X dimension include/exclude flag.
              * @param y Y dimension include/exclude flag.
              * @param z Z dimension include/exclude flag.
              */
            void setLinearFlags(int x, int y, int z);
            /**
              * @return Returns the include/exclude momentum fix for the X
              *         dimension.
              */
            int getXLinearFlag();
            /**
              * @return Returns the include/exclude momentum fix for the Y
              *         dimension.
              */
            int getYLinearFlag();
            /**
              * @return Returns the include/exclude momentum fix for the Z
              *         dimension.
              */
            int getZLinearFlag();
            /**
              * @return Returns the number of timesteps between adjusting the
              *         momentum.
              */
            int getSteps();
            /**
              * @return Returns keyword to the native Lammps simulation momentum
              *         fix command.  Possible values :
              *   LINEAR  = 0
              *   ANGULAR = 1
              */
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
