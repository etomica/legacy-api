/*
 *  IAPISpeciesManager.h
 *  API Glue
 *
 */

#ifndef API_ISPECIESMGR_WRAPPER_H
#define API_ISPECIESMGR_WRAPPER_H

#include "IAPIBox.h"
#include "IAPISpecies.h"

namespace molesimAPI
{

    class IAPISpeciesManager {

        public:
	    virtual void removeSpecies(IAPISpecies *) = 0;
	    virtual void addSpecies(IAPISpecies *) = 0;
	    virtual void boxAddedNotify(IAPIBox *) = 0;
            virtual int getSpeciesCount() = 0; 
            virtual IAPISpecies *getSpecies(int) = 0;

    };
}

#endif
