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
              * @param species Species of molecules added to box
              * @param count Number of molecules in the box for the species
              *              related to the event.
              * @param box Box related to the event.
              */
            GlotzillaBoxMoleculeCountEvent(IAPISpecies *species, int count, IAPIBox *box);

            IAPISpecies *getSpecies();
            int getCount();

        protected:
            int mCount;
            IAPISpecies *mSpecies;

    };
}
#endif
