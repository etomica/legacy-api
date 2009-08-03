/*
 *  GlotzillaSimulationBoxEvent.cpp
 *  API Glue
 *
 */

#include "stdio.h"

#include "GlotzillaSimulationBoxEvent.h"

namespace glotzwrappers
{

    GlotzillaSimulationBoxEvent::GlotzillaSimulationBoxEvent(IAPISimulation *sim, IAPIBox *box) :
                                                         GlotzillaSimulationEvent(sim) {
        mBox = box;
    }

    /*
     * getBox()
     */
    IAPIBox *GlotzillaSimulationBoxEvent::getBox() {
        return mBox;
    }


}
