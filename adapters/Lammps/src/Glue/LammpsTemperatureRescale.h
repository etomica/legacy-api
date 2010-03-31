/*
 *  LammpsTemperatureRescale.h
 *  API Glue
 *
 */

#ifndef LAMMPS_TEMP_RESCALE_WRAPPER_H
#define LAMMPS_TEMP_RESCALE_WRAPPER_H

namespace lammpswrappers
{

    class LammpsTemperatureRescale {
        public:
            /**
              * Stores the parameters for construction of a native Lammps
              * fix ... temp/rescale command.
              * @param steps Perform rescaling every number of steps.
              * @param tStart Temperature at start of simulation.
              * @param tStop Temperature at end of simulation.
              * @param rescaleWindow Only rescale if temperature is outside
              *                      of this window.
              * @param rescaleFactor Rescale to target temperature by this
              *                      fraction.
              */
            LammpsTemperatureRescale(int steps, double tStart, double tStop,
                                     double rescaleWindow, double rescaleFactor);

            /**
              * @param state Indicate if the temperature rescale is enabled
              *              or disabled.
              */
            void setState(bool state);
            /**
              * @return Returns enabled/disabled state of temperature
              *         rescale.
              */
            bool getState();
            /**
              * @return Returns the number of rescaling steps.
              */
            int getSteps();
            /**
              * @return Returns the temperature at start of simulation
              */
            double getStart();
            /**
              * @return Returns the temperature at end of simulation
              */
            double getStop();
            /**
              * @return Returns the temperature rescaling window.
              */
            double getWindow();
            /**
              * @return Returns the temperature rescaling fraction.
              */
            double getFraction();

        private:
            bool enabled;
            int tempRescaleSteps;
            double tempRescaleStart;
            double tempRescaleStop;
            double tempRescaleWindow;
            double tempRescaleFraction;

    };
}

#endif
