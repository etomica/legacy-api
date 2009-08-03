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
              * @param index 
              * @param box Box pertaining to this event that the atom was
              *            added to.
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
