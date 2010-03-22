/*
 *  GlotzillaBoxIndexEvent.h
 *  API Glue
 *
 */

#ifndef GLOTZ_BOXINDEXEVENT_WRAPPER_H
#define GLOTZ_BOXINDEXEVENT_WRAPPER_H

#include "IAPIAtom.h"
#include "IAPIBox.h"
#include "IAPIBoxIndexEvent.h"
#include "GlotzillaBoxEvent.h"

using namespace molesimAPI;

namespace glotzwrappers
{

    /**
      */
    class GlotzillaBoxIndexEvent : public GlotzillaBoxEvent,
                                  public virtual IAPIBoxIndexEvent {

        public:
            /**
              * @param index index of box pertaining to this event.
              * @param box Box pertaining to this event.
              */
            GlotzillaBoxIndexEvent(int index, IAPIBox *box);

            /**
              * @return 
              */
            int getIndex();

        protected:
            int mIndex;

    };
}
#endif
