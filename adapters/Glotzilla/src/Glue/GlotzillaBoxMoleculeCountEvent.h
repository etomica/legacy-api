/*
 *  GlotzillaBoxMoleculeCountEvent.h
 *  API Glue
 *
 */

#ifndef GLOTZ_BOXMOLECOUNTEVENT_WRAPPER_H
#define GLOTZ_BOXMOLECOUNTEVENT_WRAPPER_H

#include "IAPIBox.h"
#include "IAPIBoxMoleculeCountEvent.h"
#include "IAPISpecies.h"
#include "GlotzillaBoxEvent.h"

using namespace molesimAPI;

namespace glotzwrappers
{

    /**
      */
    class GlotzillaBoxMoleculeCountEvent : public GlotzillaBoxEvent,
                                  public virtual IAPIBoxMoleculeCountEvent {

        public:
            /**
              * @param species 
              * @param count 
              * @param box 
              */
            GlotzillaBoxMoleculeCountEvent(IAPISpecies *species, int count, IAPIBox *box);

            /**
              * @return
              */
            IAPISpecies *getSpecies();
            /**
              * @return
              */
            int getCount();

        protected:
            int mCount;
            IAPISpecies *mSpecies;

    };
}
#endif
