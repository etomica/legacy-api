/*
 *  IAPISimulationIndexEvent.h
 *  API Glue
 *
 */

#ifndef API_ISIMULATIONINDEXEVENT_WRAPPER_H
#define API_ISIMULATIONINDEXEVENT_WRAPPER_H

#include "IAPISimulationEvent.h"

namespace molesimAPI
{

    class IAPISimulationIndexEvent : public virtual IAPISimulationEvent {

        public:			
            virtual int getIndex() = 0;
    };
}
#endif
