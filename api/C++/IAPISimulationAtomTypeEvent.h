/*
 *  IAPISimulationAtomTypeEvent.h
 *  API Glue
 *
 */

#ifndef API_ISIMULATIONATOMTYPEEVENT_WRAPPER_H
#define API_ISIMULATIONATOMTYPEEVENT_WRAPPER_H

#include "IAPIAtomType.h"
#include "IAPISimulationEvent.h"

namespace molesimAPI
{

    class IAPISimulationAtomTypeEvent : public virtual IAPISimulationEvent {

        public:
            /**
              * @return Returns the atom type that this event is related to.
              */
            virtual IAPIAtomType *getAtomType() = 0;
    };
}
#endif
