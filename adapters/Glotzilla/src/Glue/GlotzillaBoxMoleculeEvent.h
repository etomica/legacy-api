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

    class GlotzillaBoxMoleculeEvent : public GlotzillaBoxEvent,
                                  public virtual IAPIBoxMoleculeEvent {

        public:
            /**
              * @param mole Molecule added to the box that the event pertains to.
              * @param box Box pertaining to this event that the molecule was
              *            added to.
              */
            GlotzillaBoxMoleculeEvent(IAPIMolecule *mole, IAPIBox *box);

            IAPIMolecule *getMolecule();

        protected:
            IAPIMolecule *mMolecule;

    };
}
#endif
