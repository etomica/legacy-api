/*
 *  LammpsTemperatureRescale.cpp
 *  API Glue
 *
 */

#include "library.h"

#include "LammpsTemperatureRescale.h"

namespace lammpswrappers
{

    LammpsTemperatureRescale::LammpsTemperatureRescale(
                            int steps, double tStart, double tStop,
                            double rescaleWindow, double rescaleFactor) {
        enabled = true;
        tempRescaleSteps = steps;
        tempRescaleStart = tStart;
        tempRescaleStop = tStop;
        tempRescaleWindow = rescaleWindow;
        tempRescaleFraction = rescaleFactor;
    }

    /*
     * setState
     */
    void LammpsTemperatureRescale::setState(bool state) {
        enabled = state;
    }

    /*
     * getState
     */
    bool LammpsTemperatureRescale::getState() {
        return enabled;
    }

    /*
     * getSteps
     */
    int LammpsTemperatureRescale::getSteps() {
        return tempRescaleSteps;
    }

    /*
     * getStart
     */
    double LammpsTemperatureRescale::getStart() {
        return tempRescaleStart;
    }

    /*
     * getStop
     */
    double LammpsTemperatureRescale::getStop() {
        return tempRescaleStop;
    }

    /*
     * getWindow
     */
    double LammpsTemperatureRescale::getWindow() {
        return tempRescaleWindow;
    }

    /*
     * getFraction
     */
    double LammpsTemperatureRescale::getFraction() {
        return tempRescaleFraction;
    }

}
