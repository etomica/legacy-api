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
#include "IAPIAtomPositioned.h"
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
            /**
              * Sets the index for the box.  The index is the position
              * in the list of boxes held by the simulation.
              * WARNING : This should only be called from the simulation.
              * @param newIndex The box's new index
              */
            void setIndex(int newIndex);
            /**
              * Returns the box's index.  The index is the position
              * in the list of boxes held by the simulation.
              * @return Returns the box's index
              */
            int getIndex();
            /**
              * Adds a molecule to the box.  The molecule should be a member
              * of a species that had been added to the species manager.  The
              * molecule should NOT already be in this box or any other box.
              * @param mole Molecule to add to the box
              */
            void addMolecule(IAPIMolecule *mole);
            /**
              * Remove a molecule from the box.
              * @param mole The molecule to remove from the box.
              */
            void removeMolecule(IAPIMolecule *mole);
            /**
              * Set the number of molecules for the box to the given value
              * for the species requested.  Molecules will be added or
              * deleted as necessary to fulfill the request.
              * @param species Add/delete molecules of this species to
              *                process the request.
              * @param numMolecules The number of molecules that should
              *                      be in the box (of the given species).
              */
            void setNMolecules(IAPISpecies *species, int numMolecules);
            /**
              * @param species Only consider molecules of this species.
              * @return Returns the number of species in the box for the
              *         given species.
              */
            int getNMolecules(IAPISpecies *species);
            /**
              * Return a list of molecules of the given species in the box.
              * @param species Populate the list returned only with molecules
              *                of this species.
              * @return Return a list of the molecules in the box of the
              *         given species.
              */
            IAPIMoleculeList *getMoleculeList(IAPISpecies *species);
            /**
              * @return Return a list of all the molecules in the box.
              */
            IAPIMoleculeList *getMoleculeList();
            /**
              * @return Return a list of all the atoms in the box.
              */
            IAPIAtomList *getLeafList();
            /**
              * @return Return the box's boundary.
              */
            IAPIBoundary *getBoundary();
            /**
              * Set the box's boundary to the given boundary.
              * @param boundary Box's new boundary.
              */
            void setBoundary(IAPIBoundary *boundary);
            /**
              * @return Returns the event manager for the box.
              */
            IAPIBoxEventManager *getEventManager();
            /**
              * Notify the box that a species has been added to the
              * simulation.
              * WARNING : Only the he simulation's species manager should
              *           call this method
              * @param species Species added to the simulation.
              * @todo The species manager should call this method.  This is
              *       not implemented.  Currently, the driver is calling
              *       the method.  That is NOT OK.
              */
            void addSpeciesNotify(IAPISpecies *species);
            /**
              * Notify the box that a species has been removed from the
              * simulation.
              * WARNING : Only the he simulation's species manager should
              *           call this method
              * @param species Species removed from the simulation.
              * @todo The species manager should call this method.  This is
              *       not implemented.  Currently, the driver is calling
              *       the method.  That is NOT OK.
              */
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
