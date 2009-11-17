/*
 *  TowheeBoxMoleculeCountEvent.h
 *  API Glue
 *
 */

#ifndef TOWHEE_BOXMOLECOUNTEVENT_WRAPPER_H
#define TOWHEE_BOXMOLECOUNTEVENT_WRAPPER_H

#include "IAPIBox.h"
#include "IAPIBoxMoleculeCountEvent.h"
#include "IAPISpecies.h"
#include "TowheeBoxEvent.h"

using namespace molesimAPI;

namespace towheesnifferwrappers
{

    /**
      */
    class TowheeBoxMoleculeCountEvent : public TowheeBoxEvent,
                                  public virtual IAPIBoxMoleculeCountEvent {

        public:
            /**
              * @param species 
              * @param count 
              * @param box 
              */
            TowheeBoxMoleculeCountEvent(IAPISpecies *species, int count, IAPIBox *box);

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
