/*
 *  IAPIBoxAtomEvent.h
 *  API Glue
 *
 */

#ifndef API_IBOXATOMEVENT_WRAPPER_H
#define API_IBOXATOMEVENT_WRAPPER_H

#include "IAPIAtom.h"
#include "IAPIBoxEvent.h"

namespace molesimAPI
{

    class IAPIBoxAtomEvent : public virtual IAPIBoxEvent {

        public:			
            virtual IAPIAtom *getAtom() = 0;
    };
}
#endif
