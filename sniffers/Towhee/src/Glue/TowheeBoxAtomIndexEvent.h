/*
 *  TowheeBoxAtomIndexEvent.h
 *  API Glue
 *
 */

#ifndef TOWHEE_BOXATOMINDEXEVENT_WRAPPER_H
#define TOWHEE_BOXATOMINDEXEVENT_WRAPPER_H

#include "IAPIBox.h"
#include "IAPIBoxAtomIndexEvent.h"
#include "TowheeBoxAtomEvent.h"

using namespace molesimAPI;

namespace towheesnifferwrappers
{

    /**
      */
    class TowheeBoxAtomIndexEvent : public TowheeBoxAtomEvent,
                                  public virtual IAPIBoxAtomIndexEvent {

        public:
            int getIndex();

    };
}
#endif
