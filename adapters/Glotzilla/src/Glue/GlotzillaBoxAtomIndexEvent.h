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
              * @param atom Atom in the box that the event pertians to.
              * @param index new index of the atom in the box.
              * @param box Box pertaining to this event.
              */
            GlotzillaBoxAtomIndexEvent(IAPIAtom *atom, int index, IAPIBox *box);
            int getIndex();

        protected:
            int mIndex;

    };
}
#endif
