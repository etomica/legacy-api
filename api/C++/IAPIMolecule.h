/*
 *  IAPIMolecule.h
 *  API Glue
 *
 */

#ifndef API_IMOLECULE_WRAPPER_H
#define API_IMOLECULE_WRAPPER_H

#include "IAPIAtom.h"
#include "IAPIAtomPositioned.h"
#include "IAPIAtomList.h"
#include "IAPISpecies.h"

namespace molesimAPI
{

    class IAPIMolecule {

        public:			
            virtual int getIndex() = 0;
            virtual void setIndex(int) = 0;
            virtual void addChildAtom(IAPIAtom *) = 0;
            virtual void removeChildAtom(IAPIAtom *) = 0;
            virtual IAPIAtomList *getChildList() = 0;
            virtual IAPISpecies *getType() = 0;

    };
}
#endif
