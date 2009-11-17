/*
 *  TowheeBoxAtomEvent.h
 *  API Glue
 *
 */

#ifndef TOWHEE_BOXATOMEVENT_WRAPPER_H
#define TOWHEE_BOXATOMEVENT_WRAPPER_H

#include "IAPIBox.h"
#include "IAPIBoxAtomEvent.h"
#include "TowheeBoxEvent.h"

using namespace molesimAPI;

namespace towheesnifferwrappers
{

    /**
      * TowheeBoxAtomEvent is an event superclass for events that are
      * related to an atom's interaction with a box (addtion to, removal
      * from, etc...).
      */
    class TowheeBoxAtomEvent : public TowheeBoxEvent,
                                  public virtual IAPIBoxAtomEvent {

        public:
            IAPIAtom *getAtom();

    };
}
#endif
