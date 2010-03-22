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
            /**
              * This method is not implemented.
              */
            void removeMolecule(IAPIMolecule *mole);
            /**
              * Set the number of molecules for the box to the given value
              * for the species requested.  Molecules will be added to
              * fulfill the request.
              * NOTE : This method cannot be used to remove molecules from
              *        the box.
              * @param species Add molecules of this species to process the
              *                request.
              * @param numMolecules The number of molecules that should
              *                      be in the box (of the given species).
              */
            void setNMolecules(IAPISpecies *species, int numMolecules);
            /**
              * Determines the number of molecules, of the given species,
              * by reaching into the native Towee simulation (twh_initmol).
              * @param species Only consider molecules of this species.
              * @return Returns the number of species in the box for the
              *         given species.
              */
            int getNMolecules(IAPISpecies *species);
            IAPIMoleculeList *getMoleculeList(IAPISpecies *);
            IAPIMoleculeList *getMoleculeList();
            IAPIAtomList *getLeafList();
            IAPIBoundary *getBoundary();
            void setBoundary(IAPIBoundary *);
            IAPIBoxEventManager *getEventManager();
            void addSpeciesNotify(IAPISpecies *species);
            /**
              * This method is not implemented.
              */
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
