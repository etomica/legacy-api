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
            LammpsTemperatureRescale(int steps, double tStart, double tStop,
                                     double rescaleWindow, double rescaleFactor);
            void setState(bool state);
            bool getState();
            int getSteps();
            double getStart();
            double getStop();
            double getWindow();
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
