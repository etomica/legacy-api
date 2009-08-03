/*
 *  IAPISimulationBoxEvent.h
 *  API Glue
 *
 */

#ifndef API_ISIMULATIONBOXEVENT_WRAPPER_H
#define API_ISIMULATIONBOXEVENT_WRAPPER_H

#include "IAPISimulationEvent.h"

namespace molesimAPI
{

    class IAPIBox;

    class IAPISimulationBoxEvent : public virtual IAPISimulationEvent {

        public:			
            virtual IAPIBox *getBox() = 0;
    };
}
#endif
