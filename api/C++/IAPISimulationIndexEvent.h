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
            /**
              * @return Returns the index that this event is related to.
              */
            virtual int getIndex() = 0;
    };
}
#endif
