/*
 *  IAPIBox.h
 *  API Glue
 *
 */

#ifndef API_IBOX_WRAPPER_H
#define API_IBOX_WRAPPER_H

#include "IAPIAtom.h"
#include "IAPIAtomList.h"
#include "IAPIBoundary.h"
#include "IAPIMolecule.h"
#include "IAPIBoxEventManager.h"
#include "IAPIMoleculeList.h"

namespace molesimAPI
{

    class IAPISimulation;
    class IAPISpecies;
//    class IAPIMoleculeList;

    class IAPIBox {

        public:
		
            virtual void setIndex(int) = 0;
            virtual int getIndex() = 0;
            virtual void addMolecule(IAPIMolecule *) = 0;
            virtual void removeMolecule(IAPIMolecule *) = 0;
            virtual void setNMolecules(IAPISpecies *, int) = 0;
            virtual int  getNMolecules(IAPISpecies *) = 0;
            virtual IAPIMoleculeList *getMoleculeList(IAPISpecies *) = 0;
            virtual IAPIMoleculeList *getMoleculeList() = 0;
            virtual IAPIAtomList *getLeafList() = 0;
            virtual IAPIBoundary *getBoundary() = 0;
            virtual void setBoundary(IAPIBoundary *) = 0;
            virtual IAPIBoxEventManager *getEventManager() = 0;
            virtual void addSpeciesNotify(IAPISpecies *) = 0;
            virtual void removeSpeciesNotify(IAPISpecies *) = 0;

    };
}

#endif
