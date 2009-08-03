/*
 *  IAPIBoxMoleculeCountEvent.h
 *  API Glue
 *
 */

#ifndef API_IBOXMOLECULECOUNTEVENT_WRAPPER_H
#define API_IBOXMOLECULECOUNTEVENT_WRAPPER_H

#include "IAPIBoxEvent.h"
#include "IAPISpecies.h"

namespace molesimAPI
{

    class IAPIBoxMoleculeCountEvent : public virtual IAPIBoxEvent {

        public:
            virtual IAPISpecies *getSpecies() = 0;
            virtual int getCount() = 0;
    };
}
#endif
