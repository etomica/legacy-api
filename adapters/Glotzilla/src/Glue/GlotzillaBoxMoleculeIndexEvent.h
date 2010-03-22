/*
 *  GlotzillaBoxMoleculeIndexEvent.h
 *  API Glue
 *
 */

#ifndef GLOTZ_BOXMOLEINDEXEVENT_WRAPPER_H
#define GLOTZ_BOXMOLEINDEXEVENT_WRAPPER_H

#include "IAPIBox.h"
#include "IAPIBoxMoleculeIndexEvent.h"
#include "GlotzillaBoxMoleculeEvent.h"

using namespace molesimAPI;

namespace glotzwrappers
{

    /**
      */
    class GlotzillaBoxMoleculeIndexEvent : public GlotzillaBoxMoleculeEvent,
                                  public virtual IAPIBoxMoleculeIndexEvent {

        public:
            /**
              * @param mole Molecule related to the event.
              * @param index Index related to the event.
              * @param box Box related to the event.
              */
            GlotzillaBoxMoleculeIndexEvent(IAPIMolecule *mole, int index, IAPIBox *box);

            int getIndex();

        protected:
            int mIndex;

    };
}
#endif
