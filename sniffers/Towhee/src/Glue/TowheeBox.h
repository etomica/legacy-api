/*
 *  TowheeBox.h
 *  API Glue
 *
 */

#ifndef TOWHEE_BOX_WRAPPER_H
#define TOWHEE_BOX_WRAPPER_H

#include "IAPIAtom.h"
#include "IAPIBoundary.h"
#include "IAPIBox.h"
#include "IAPIBoxEventManager.h"
#include "IAPIAtomList.h"
#include "IAPIMolecule.h"
#include "IAPIMoleculeList.h"
#include "IAPISpecies.h"
#include "IAPISimulation.h"
#include "TowheeAtomList.h"
#include "TowheeMoleculeList.h"

using namespace molesimAPI;

namespace towheesnifferwrappers
{

    class TowheeBox : public virtual IAPIBox {

        public:

            TowheeBox();

            void setIndex(int newIndex);
            int getIndex();
            void addMolecule(IAPIMolecule *mole);
            void removeMolecule(IAPIMolecule *mole);
            void setNMolecules(IAPISpecies *species, int numMolecules);
            int getNMolecules(IAPISpecies *species);
            IAPIMoleculeList *getMoleculeList(IAPISpecies *species);
            IAPIMoleculeList *getMoleculeList();
            IAPIAtomList *getLeafList();
            IAPIBoundary *getBoundary();
            void setBoundary(IAPIBoundary *boundary);
            IAPIBoxEventManager *getEventManager();
            void addSpeciesNotify(IAPISpecies *species);
            void removeSpeciesNotify(IAPISpecies *species);

        private:
            IAPIBoxEventManager *mEventManager;
            IAPIBoundary *mBoundary;
            int mIndex; // Add 1 to get towhee index
            TowheeMoleculeList *mMoleList;
            TowheeMoleculeList *mMoleListBySpecies;
            TowheeAtomList *mLeafList;
    };
}

#endif
