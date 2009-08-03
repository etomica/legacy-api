/*
 *  GlotzillaBoxAtomIndexEvent.h
 *  API Glue
 *
 */

#ifndef GLOTZ_BOXATOMINDEXEVENT_WRAPPER_H
#define GLOTZ_BOXATOMINDEXEVENT_WRAPPER_H

#include "IAPIBox.h"
#include "IAPIBoxAtomIndexEvent.h"
#include "GlotzillaBoxAtomEvent.h"

using namespace molesimAPI;

namespace glotzwrappers
{

    /**
      */
    class GlotzillaBoxAtomIndexEvent : public GlotzillaBoxAtomEvent,
                                  public virtual IAPIBoxAtomIndexEvent {

        public:
            /**
              * @param atom Atom added to the box that the event pertians to.
              * @param box Box pertaining to this event that the atom was
              *            added to.
              */
            GlotzillaBoxAtomIndexEvent(IAPIAtom *atom, int index, IAPIBox *box);

            /**
              * @return Returns the atom related to this event.
              */
            int getIndex();

        protected:
            int mIndex;

    };
}
#endif
