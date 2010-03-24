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
            /**
              * @return Returns the box that this event is related to.
              */
            virtual IAPIBox *getBox() = 0;
    };
}
#endif
