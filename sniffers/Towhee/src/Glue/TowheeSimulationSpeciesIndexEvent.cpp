/*
 *  TowheeSimulationSpeciesIndexEvent.cpp
 *  API Glue
 *
 */

#include "TowheeSimulationSpeciesIndexEvent.h"

namespace towheesnifferwrappers
{

    TowheeSimulationSpeciesIndexEvent::TowheeSimulationSpeciesIndexEvent(IAPISimulation *sim, IAPISpecies *box, int idx) :
                                                         TowheeSimulationSpeciesEvent(sim, box) {
        mIndex = idx;
    }

    /*
     * getIndex()
     */
    int TowheeSimulationSpeciesIndexEvent::getIndex() {
        return mIndex;
    }


}
