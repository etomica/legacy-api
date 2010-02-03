/*
 *  LammpsBox.h
 *  API Glue
 *
 */

#ifndef LAMMPS_BOX_WRAPPER_H
#define LAMMPS_BOX_WRAPPER_H

#include <map>
#include <string>
#include <vector>

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
#include "LammpsMolecule.h"
#include "LammpsMoleculeList.h"
#include "LammpsSimulation.h"
#include "LammpsSpecies.h"

#include "ObjectManager.h"

using namespace molesimAPI;

namespace lammpssnifferwrappers
{

    class LammpsBox : public virtual IAPIBox {

        public:

            LammpsBox(LammpsSimulation *sim, IAPIBoundary *boundary, std::vector<LammpsSpecies *>, std::vector<LammpsMolecule *>);

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

        protected:
            IAPIBoundary *mBoundary;
            int mIndex; // Index of box in simulation (-1 indicates not in simulation)
            LammpsMoleculeList *mMolecules;

        private:
            LammpsSimulation *mSim;
            void lammpsSetup();
//            int numberAtomTypes();
//            ObjectManager *objectManager;
            std::map<IAPISpecies *, int> speciesList;
            LammpsAtomList *mLeafList;
            LammpsMoleculeList *mMoleListBySpecies;
            LammpsBoxEventManager *mBoxEvtMgr;
            static const int INDEX_UNASSIGNED;
    };
}

#endif
