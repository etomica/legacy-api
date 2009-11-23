/*
 *  TowheeBox.h
 *  API Glue
 *
 */

#ifndef TOWHEE_BOX_WRAPPER_H
#define TOWHEE_BOX_WRAPPER_H

#include <map>

#include "IAPIAtom.h"
#include "IAPIBoundary.h"
#include "IAPIBox.h"
#include "IAPIBoxEventManager.h"
#include "IAPIAtomList.h"
#include "IAPIMolecule.h"
#include "IAPIMoleculeList.h"
#include "IAPISimulation.h"
#include "IAPISpecies.h"
#include "TowheeBoxEventManager.h"
#include "TowheeAtomList.h"
#include "TowheeMoleculeList.h"

using namespace molesimAPI;

namespace towheewrappers
{

    class TowheeBox : public virtual IAPIBox {

        public:

            TowheeBox();

            // API Compliance
            void setIndex(int newIndex);
            int getIndex();
            void addMolecule(IAPIMolecule *mole);
            void removeMolecule(IAPIMolecule *mole);
            void setNMolecules(IAPISpecies *species, int numMolecules);
            int getNMolecules(IAPISpecies *species);
            IAPIMoleculeList *getMoleculeList(IAPISpecies *);
            IAPIMoleculeList *getMoleculeList();
            IAPIAtomList *getLeafList();
            IAPIBoundary *getBoundary();
            void setBoundary(IAPIBoundary *);
            IAPIBoxEventManager *getEventManager();
            void addSpeciesNotify(IAPISpecies *species);
            void removeSpeciesNotify(IAPISpecies *species);

        private:
            void addNewMolecule(IAPISpecies *species);
            IAPIBoundary *mBoundary;
            int mIndex; // Index of box in simulation (-1 indicates not in simulation)
            TowheeBoxEventManager *mBoxEvtMgr;
            std::map<IAPISpecies *, int> mSpeciesCount;
            TowheeMoleculeList *mMolecules;
            TowheeAtomList *mLeafList;
            TowheeMoleculeList *mMoleListBySpecies;
    };
}

#endif
