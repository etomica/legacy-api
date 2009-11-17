/*
 *  TowheeSimulationBoxEvent.cpp
 *  API Glue
 *
 */

#include "stdio.h"

#include "TowheeSimulationBoxEvent.h"

namespace towheesnifferwrappers
{

    TowheeSimulationBoxEvent::TowheeSimulationBoxEvent(IAPISimulation *sim, IAPIBox *box) :
                                                         TowheeSimulationEvent(sim) {
        mBox = box;
    }

    /*
     * getBox()
     */
    IAPIBox *TowheeSimulationBoxEvent::getBox() {
        return mBox;
    }


}
