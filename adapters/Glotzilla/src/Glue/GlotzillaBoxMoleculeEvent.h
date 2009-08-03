/*
 *  GlotzillaBoxMoleculeEvent.h
 *  API Glue
 *
 */

#ifndef GLOTZ_BOXMOLECULEEVENT_WRAPPER_H
#define GLOTZ_BOXMOLECULEEVENT_WRAPPER_H

#include "IAPIBox.h"
#include "IAPIBoxMoleculeEvent.h"
#include "IAPIMolecule.h"
#include "GlotzillaBoxEvent.h"

using namespace molesimAPI;

namespace glotzwrappers
{

    /**
      * GlotzillaBoxMoleculeEvent is an event superclass for events that are
      * related to an molecules's interaction with a box (addtion to, removal
      * from, etc...).
      */
    class GlotzillaBoxMoleculeEvent : public GlotzillaBoxEvent,
                                  public virtual IAPIBoxMoleculeEvent {

        public:
            /**
              * @param mole Molecule added to the box that the event pertians to.
              * @param box Box pertaining to this event that the molecule was
              *            added to.
              */
            GlotzillaBoxMoleculeEvent(IAPIMolecule *mole, IAPIBox *box);

            /**
              * @return Returns the atom related to this event.
              */
            IAPIMolecule *getMolecule();

        protected:
            IAPIMolecule *mMolecule;

    };
}
#endif
