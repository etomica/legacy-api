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
            /**
              * @return Returns the species of the newly added molecules.
              */
            virtual IAPISpecies *getSpecies() = 0;
            /**
              * @return Returns the number of molecules in the box for the
              *         species related to the event.
              */
            virtual int getCount() = 0;
    };
}
#endif
