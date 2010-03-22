/*
 *  IAPIBoxIndexEvent.h
 *  API Glue
 *
 */

#ifndef API_IBOXINDEXEVENT_WRAPPER_H
#define API_IBOXINDEXEVENT_WRAPPER_H

#include "IAPIBoxEvent.h"

namespace molesimAPI
{

    class IAPIBoxIndexEvent : public virtual IAPIBoxEvent {

        public:
            /**
              * @return Box index related to the event.
              */
            virtual int getIndex() = 0;
    };
}
#endif
