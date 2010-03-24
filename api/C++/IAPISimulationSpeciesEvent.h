/*
 *  IAPISimulationSpeciesEvent.h
 *  API Glue
 *
 */

#ifndef API_ISIMULATIONSPECIESEVENT_WRAPPER_H
#define API_ISIMULATIONSPECIESEVENT_WRAPPER_H

#include "IAPISpecies.h"
#include "IAPISimulationEvent.h"

namespace molesimAPI
{

    class IAPISimulationSpeciesEvent : public virtual IAPISimulationEvent {

        public:			
            /**
              * @return Returns the species that this event is related to.
              */
            virtual IAPISpecies *getSpecies() = 0;
    };
}
#endif
