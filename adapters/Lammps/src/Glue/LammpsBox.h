/*
 *  LammpsBox.h
 *  API Glue
 *
 */

#ifndef LAMMPS_BOX_WRAPPER_H
#define LAMMPS_BOX_WRAPPER_H

#include <string>
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
#include "LammpsAtomList.h"
#include "LammpsBoxEventManager.h"
#include "LammpsMoleculeList.h"
#include "LammpsSimulation.h"

#include "ObjectManager.h"

using namespace molesimAPI;

namespace lammpswrappers
{

    class LammpsSimulation;

    class LammpsBox : public virtual IAPIBox {

        public:

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
            int getNMolecules(IAPISpecies *species);
            IAPIMoleculeList *getMoleculeList(IAPISpecies *);
            IAPIMoleculeList *getMoleculeList();
            IAPIAtomList *getLeafList();
            IAPIBoundary *getBoundary();
            void setBoundary(IAPIBoundary *);
            IAPIBoxEventManager *getEventManager();
            void addSpeciesNotify(IAPISpecies *species);
            void removeSpeciesNotify(IAPISpecies *species);

            // Non-API
            /**
              * Static method to create a towhee box.
              * @param sim Simulation that cox should be created in.
              */
            static LammpsBox* instance(IAPISimulation *sim);

        protected:
            LammpsSimulation *mSim;
            IAPIBoundary *mBoundary;
            int mIndex; // Index of box in simulation (-1 indicates not in simulation)
            LammpsMoleculeList *mMolecules;

        private:
            LammpsBox() {};
            LammpsBox(LammpsBox *) {};
            LammpsBox(IAPISimulation *sim);
            static LammpsBox *mInstance;
            void lammpsSetup();
            int numberAtomTypes();
            IAPIMolecule *addNewMolecule(IAPISpecies *species);
            ObjectManager *objectManager;
            std::map<IAPISpecies *, int> speciesList;
            LammpsAtomList *mLeafList;
            LammpsMoleculeList *mMoleListBySpecies;
            LammpsBoxEventManager *mBoxEvtMgr;
            static const int INDEX_UNASSIGNED;
    };
}

#endif
