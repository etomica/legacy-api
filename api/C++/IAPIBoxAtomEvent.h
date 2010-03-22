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

    /**
      * IAPIBoxAtomEvent is an event superclass for events that are
      * related to an atom's interaction with a box (addtion to, removal
      * from, etc...).
      */
    class IAPIBoxAtomEvent : public virtual IAPIBoxEvent {

        public:
            /**
              * @return Returns the atom related to this event.
              */
            virtual IAPIAtom *getAtom() = 0;
    };
}
#endif
