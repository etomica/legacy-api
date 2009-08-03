/*
 *  GlotzillaBoxEvent.h
 *  API Glue
 *
 */

#ifndef GLOTZ_BOXEVENT_WRAPPER_H
#define GLOTZ_BOXEVENT_WRAPPER_H

#include "IAPIBox.h"
#include "IAPIBoxEvent.h"

using namespace molesimAPI;

namespace glotzwrappers
{

    /**
      * GlotzillaBoxEvent is an event superclass for events that are
      * related to some event within a box.
      */
    class GlotzillaBoxEvent : public virtual IAPIBoxEvent {

        public:
            /**
              * @param box Box pertaining to this event.
              */
            GlotzillaBoxEvent(IAPIBox *box);

            /**
              * @return Returns the box that this event is related to.
              */
            IAPIBox *getBox();

        protected:
            IAPIBox *mBox;

    };
}
#endif
