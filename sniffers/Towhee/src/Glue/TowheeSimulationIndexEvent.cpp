/*
 *  TowheeSimulationIndexEvent.cpp
 *  API Glue
 *
 */

#include "stdio.h"

#include "TowheeSimulationIndexEvent.h"

namespace towheesnifferwrappers
{

    TowheeSimulationIndexEvent::TowheeSimulationIndexEvent(IAPISimulation *sim, int idx) :
                                                         TowheeSimulationEvent(sim) {
        mIndex = idx;
    }

    /*
     * getIndex()
     */
    int TowheeSimulationIndexEvent::getIndex() {
        return mIndex;
    }


}
