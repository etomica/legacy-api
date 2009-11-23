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

            // Non-API
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
