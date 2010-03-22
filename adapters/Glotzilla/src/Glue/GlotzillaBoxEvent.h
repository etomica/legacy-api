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

    class GlotzillaBoxEvent : public virtual IAPIBoxEvent {

        public:
            /**
              * @param box Box pertaining to this event.
              */
            GlotzillaBoxEvent(IAPIBox *box);
            IAPIBox *getBox();

        protected:
            IAPIBox *mBox;

    };
}
#endif
