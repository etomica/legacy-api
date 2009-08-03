/*
 *  IAPIBoxMoleculeIndexEvent.h
 *  API Glue
 *
 */

#ifndef API_IBOXMOLECULEINDEXEVENT_WRAPPER_H
#define API_IBOXMOLECULEINDEXEVENT_WRAPPER_H

#include "IAPIBoxMoleculeEvent.h"

namespace molesimAPI
{

    class IAPIBoxMoleculeIndexEvent : public virtual IAPIBoxMoleculeEvent {

        public:			
            virtual int getIndex() = 0;
    };
}
#endif
