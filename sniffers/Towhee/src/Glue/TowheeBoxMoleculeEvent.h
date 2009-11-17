/*
 *  TowheeBoxMoleculeEvent.h
 *  API Glue
 *
 */

#ifndef TOWHEE_BOXMOLECULEEVENT_WRAPPER_H
#define TOWHEE_BOXMOLECULEEVENT_WRAPPER_H

#include "IAPIBox.h"
#include "IAPIBoxMoleculeEvent.h"
#include "IAPIMolecule.h"
#include "TowheeBoxEvent.h"

using namespace molesimAPI;

namespace towheesnifferwrappers
{

    /**
      * TowheeBoxMoleculeEvent is an event superclass for events that are
      * related to an molecules's interaction with a box (addtion to, removal
      * from, etc...).
      */
    class TowheeBoxMoleculeEvent : public TowheeBoxEvent,
                                  public virtual IAPIBoxMoleculeEvent {

        public:
            /**
              * @param mole Molecule added to the box that the event pertians to.
              * @param box Box pertaining to this event that the molecule was
              *            added to.
              */
            TowheeBoxMoleculeEvent(IAPIMolecule *mole, IAPIBox *box);

            /**
              * @return Returns the atom related to this event.
              */
            IAPIMolecule *getMolecule();

        protected:
            IAPIMolecule *mMolecule;

    };
}
#endif
