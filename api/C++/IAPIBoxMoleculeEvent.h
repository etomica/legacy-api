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

    class IAPIBoxMoleculeEvent : public virtual IAPIBoxEvent {

        public:
            virtual IAPIMolecule *getMolecule() = 0;
    };
}
#endif
