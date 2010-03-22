/*
 *  GlotzillaBox.h
 *  API Glue
 *
 */

#ifndef GLOTZ_BOX_WRAPPER_H
#define GLOTZ_BOX_WRAPPER_H

#include <string>
#include <glotzmd.h>

#include "IAPIAtom.h"
#include "IAPIBoundary.h"
#include "IAPIBox.h"
#include "IAPIBoxEventManager.h"
#include "IAPIAtomList.h"
#include "IAPIMolecule.h"
#include "IAPIMoleculeList.h"
#include "IAPISpecies.h"
#include "IAPISimulation.h"
#include "GlotzillaAtomList.h"
#include "GlotzillaBoundary.h"
#include "GlotzillaBoxEventManager.h"
#include "GlotzillaMoleculeList.h"

#include "ObjectManager.h"

using namespace molesimAPI;

namespace glotzwrappers
{

    /**
      * Is a singleton class.
      * Description of GlotzillaBox here.
      * holds an instance of GlotzillaBoundary subclass.
      */
    class GlotzillaBox : public virtual IAPIBox {

        public:
            ~GlotzillaBox();

            // API Compliance
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

            // Non-API methods
            /**
              * The factory method that returns the instance of this
              * singleton class.  If the instance does not exist, the
              * instance is created.
              * @param sim Simulation that the box belongs to.
              */
            static GlotzillaBox* instance(glotzmd::Simulation *sim);

        protected:
            glotzmd::Simulation* mSimulation;
            GlotzillaBoundary *mBoundary;
            GlotzillaBoxEventManager *mBoxEvtMgr;
            int mIndex; // Index of box in simulation (-1 indicates not in simulation)

        private:
            /**
              * Constructor that generates a box.
              * @param sim Simulation that the box belongs to.
              */
            GlotzillaBox(glotzmd::Simulation* sim);
            GlotzillaBox() {};
            GlotzillaBox(GlotzillaBox *) {};
            static GlotzillaBox *mInstance;
            IAPIMolecule *addNewMolecule(IAPISpecies *species);
            ObjectManager *objectManager;
            // The leafList is not always valid.  It's only use is as a
            // return object for a call to getLeafList.
            GlotzillaAtomList *leafList;
            // The moleList is not always valid.  It's only use is as a
            // return object for a call to getLeafList.
            GlotzillaMoleculeList *moleList;
            static const int INDEX_UNASSIGNED;
    };
}

#endif
