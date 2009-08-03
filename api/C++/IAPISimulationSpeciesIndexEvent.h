/*
 *  IAPISimulationSpeciesIndexEvent.h
 *  API Glue
 *
 */

#ifndef API_ISIMULATIONSPECIESINDEXEVENT_WRAPPER_H
#define API_ISIMULATIONSPECIESINDEXEVENT_WRAPPER_H

#include "IAPISimulationSpeciesEvent.h"

namespace molesimAPI
{

    class IAPISimulationSpeciesIndexEvent : public virtual IAPISimulationSpeciesEvent {

        public:			
            virtual int getIndex() = 0;
    };
}
#endif
