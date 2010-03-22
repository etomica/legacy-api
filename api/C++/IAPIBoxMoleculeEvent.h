/*
 *  IAPIBoxMoleculeEvent.h
 *  API Glue
 *
 */

#ifndef API_IBOXMOLECULEEVENT_WRAPPER_H_XX
#define API_IBOXMOLECULEEVENT_WRAPPER_H_XX

#include "IAPIBoxEvent.h"
#include "IAPIMolecule.h"

namespace molesimAPI
{

    /**
      * IAPIBoxMoleculeEvent is an event superclass for events that are
      * related to an molecules's interaction with a box (addtion to, removal
      * from, etc...).
      */
    class IAPIBoxMoleculeEvent : public virtual IAPIBoxEvent {

        public:
            /**
              * @return Returns the molecule related to the event.
              */
            virtual IAPIMolecule *getMolecule() = 0;
    };
}
#endif
