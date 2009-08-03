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
              * @param species 
              * @param count 
              * @param box 
              */
            GlotzillaBoxMoleculeIndexEvent(IAPIMolecule *mole, int index, IAPIBox *box);

            /**
              * @return
              */
            int getIndex();

        protected:
            int mIndex;

    };
}
#endif
