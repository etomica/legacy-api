/*
 *  TowheeBoxMoleculeIndexEvent.h
 *  API Glue
 *
 */

#ifndef TOWHEE_BOXMOLEINDEXEVENT_WRAPPER_H
#define TOWHEE_BOXMOLEINDEXEVENT_WRAPPER_H

#include "IAPIBox.h"
#include "IAPIBoxMoleculeIndexEvent.h"
#include "TowheeBoxMoleculeEvent.h"

using namespace molesimAPI;

namespace towheesnifferwrappers
{

    /**
      */
    class TowheeBoxMoleculeIndexEvent : public TowheeBoxMoleculeEvent,
                                  public virtual IAPIBoxMoleculeIndexEvent {

        public:
            /**
              * @param species 
              * @param count 
              * @param box 
              */
            TowheeBoxMoleculeIndexEvent(IAPIMolecule *mole, int index, IAPIBox *box);

            /**
              * @return
              */
            int getIndex();

        protected:
            int mIndex;

    };
}
#endif
