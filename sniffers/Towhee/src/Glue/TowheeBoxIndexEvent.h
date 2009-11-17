/*
 *  TowheeBoxIndexEvent.h
 *  API Glue
 *
 */

#ifndef TOWHEE_BOXINDEXEVENT_WRAPPER_H
#define TOWHEE_BOXINDEXEVENT_WRAPPER_H

#include "IAPIAtom.h"
#include "IAPIBox.h"
#include "IAPIBoxIndexEvent.h"
#include "TowheeBoxEvent.h"

using namespace molesimAPI;

namespace towheesnifferwrappers
{

    /**
      */
    class TowheeBoxIndexEvent : public TowheeBoxEvent,
                                  public virtual IAPIBoxIndexEvent {

        public:
            /**
              * @param index 
              * @param box Box pertaining to this event that the atom was
              *            added to.
              */
            TowheeBoxIndexEvent(int index, IAPIBox *box);

            /**
              * @return 
              */
            int getIndex();

        protected:
            int mIndex;

    };
}
#endif
