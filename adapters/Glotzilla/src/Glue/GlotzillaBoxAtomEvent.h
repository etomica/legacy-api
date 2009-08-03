/*
 *  GlotzillaBoxAtomEvent.h
 *  API Glue
 *
 */

#ifndef GLOTZ_BOXATOMEVENT_WRAPPER_H
#define GLOTZ_BOXATOMEVENT_WRAPPER_H

#include "IAPIBox.h"
#include "IAPIBoxAtomEvent.h"
#include "GlotzillaBoxEvent.h"

using namespace molesimAPI;

namespace glotzwrappers
{

    /**
      * GlotzillaBoxAtomEvent is an event superclass for events that are
      * related to an atom's interaction with a box (addtion to, removal
      * from, etc...).
      */
    class GlotzillaBoxAtomEvent : public GlotzillaBoxEvent,
                                  public virtual IAPIBoxAtomEvent {

        public:
            /**
              * @param atom Atom added to the box that the event pertians to.
              * @param box Box pertaining to this event that the atom was
              *            added to.
              */
            GlotzillaBoxAtomEvent(IAPIAtom *atom, IAPIBox *box);

            /**
              * @return Returns the atom related to this event.
              */
            IAPIAtom *getAtom();

        protected:
            IAPIAtom *mAtom;

    };
}
#endif
