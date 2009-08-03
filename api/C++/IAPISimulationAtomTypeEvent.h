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
            virtual IAPIAtomType *getAtomType() = 0;
    };
}
#endif
