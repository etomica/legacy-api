/*
 *  IAPISimulationAtomTypeIndexEvent.h
 *  API Glue
 *
 */

#ifndef API_ISIMULATIONATOMTYPEINDEXEVENT_WRAPPER_H
#define API_ISIMULATIONATOMTYPEINDEXEVENT_WRAPPER_H

#include "IAPIAtomType.h"
#include "IAPISimulationAtomTypeEvent.h"

namespace molesimAPI
{

    class IAPISimulationAtomTypeIndexEvent : public virtual IAPISimulationAtomTypeEvent {

        public:			
            virtual int getIndex() = 0;
    };
}
#endif
