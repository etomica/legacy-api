/*
 *  IAPISpecies.h
 *  API Glue
 *
 */

#ifndef API_ISPECIES_WRAPPER_H
#define API_ISPECIES_WRAPPER_H

#include "IAPIAtomType.h"
#include "IAPIMolecule.h"
#include "IAPISpeciesManager.h"

namespace molesimAPI
{

    class IAPIAtomPositionDefinition;

    class IAPISpecies {

        public:			
	    virtual int getIndex() = 0;
	    virtual void setIndex(int) = 0;
	    virtual IAPIMolecule *makeMolecule() = 0;
            virtual int getAtomTypeCount() = 0;
            virtual IAPIAtomType *getAtomType(int index) = 0;
	    virtual void initializeConformation(IAPIMolecule *) = 0;

    };
}
#endif
