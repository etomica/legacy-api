/*
 *  IAPIBoxMoleculeIndexEvent.h
 *  API Glue
 *
 */

#ifndef API_IBOXMOLECULEINDEXEVENT_WRAPPER_H
#define API_IBOXMOLECULEINDEXEVENT_WRAPPER_H

#include "IAPIBoxMoleculeEvent.h"

namespace molesimAPI
{

    class IAPIBoxMoleculeIndexEvent : public virtual IAPIBoxMoleculeEvent {

        public:
            /**
              * @return Returns the index related to the event.
              */
            virtual int getIndex() = 0;
    };
}
#endif
