/*
 *  LammpsSimulationBoxEvent.cpp
 *  API Glue
 *
 */

#include "stdio.h"

#include "LammpsSimulationBoxEvent.h"

namespace lammpswrappers
{

    LammpsSimulationBoxEvent::LammpsSimulationBoxEvent(IAPISimulation *sim, IAPIBox *box) :
                                                         LammpsSimulationEvent(sim) {
        mBox = box;
    }

    /*
     * getBox()
     */
    IAPIBox *LammpsSimulationBoxEvent::getBox() {
        return mBox;
    }


}
