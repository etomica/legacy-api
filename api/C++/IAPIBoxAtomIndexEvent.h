/*
 *  IAPIBoxAtomIndexEvent.h
 *  API Glue
 *
 */

#ifndef API_IBOXATOMINDEXEVENT_WRAPPER_H
#define API_IBOXATOMINDEXEVENT_WRAPPER_H

#include "IAPIBoxAtomEvent.h"

namespace molesimAPI
{

    class IAPIBoxAtomIndexEvent : public virtual IAPIBoxAtomEvent {

        public:			
            virtual int getIndex() = 0;
    };
}
#endif
