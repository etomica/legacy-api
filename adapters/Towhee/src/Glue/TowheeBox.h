/*
 *  TowheeBox.h
 *  API Glue
 *
 */

#ifndef TOWHEE_BOX_WRAPPER_H
#define TOWHEE_BOX_WRAPPER_H

#include "IAPIAtom.h"
#include "IAPIAtomPositioned.h"
#include "IAPIBoundary.h"
#include "IAPIBox.h"
#include "IAPIBoxEventManager.h"
#include "IAPIAtomList.h"
#include "IAPIMolecule.h"
#include "IAPIMoleculeList.h"
#include "IAPISimulation.h"
#include "IAPISpecies.h"

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
            IAPIBoundary *mBoundary;
            int mIndex; // Index of box in simulation (-1 indicates not in simulation)
//            TowheeBoxEventManager *mBoxEvtMgr;
    };
}

#endif
