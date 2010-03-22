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

namespace molesimAPI
{

    class IAPISimulation;
    class IAPISpecies;
    class IAPIMoleculeList;

    class IAPIBox {

        public:

            /**
              * Sets the index for the box.  The index is the position
              * in the list of boxes held by the simulation.
              * WARNING : This should only be called from the simulation.
              * @param newIndex The box's new index
              */
            virtual void setIndex(int) = 0;
            /**
              * Returns the box's index.  The index is the position
              * in the list of boxes held by the simulation.
              * @return Returns the box's index
              */
            virtual int getIndex() = 0;
            /**
              * Adds a molecule to the box.  The molecule should be a member
              * of a species that had been added to the species manager.  The
              * molecule should NOT already be in this box or any other box.
              * @param mole Molecule to add to the box
              */
            virtual void addMolecule(IAPIMolecule *) = 0;
            /**
              * Remove a molecule from the box.
              * @param mole The molecule to remove from the box.
              */
            virtual void removeMolecule(IAPIMolecule *) = 0;
            /**
              * Set the number of molecules for the box to the given value
              * for the species requested.  Molecules will be added or
              * deleted as necessary to fulfill the request.
              * @param species Add/delete molecules of this species to
              *                process the request.
              * @param numMolecules The number of molecules that should
              *                      be in the box (of the given species).
              */
            virtual void setNMolecules(IAPISpecies *, int) = 0;
            /**
              * @param species Only consider molecules of this species.
              * @return Returns the number of species in the box for the
              *         given species.
              */
            virtual int  getNMolecules(IAPISpecies *) = 0;
            /**
              * Return a list of molecules of the given species in the box.
              * @param species Populate the list returned only with molecules
              *                of this species.
              * @return Return a list of the molecules in the box of the
              *         given species.
              */
            virtual IAPIMoleculeList *getMoleculeList(IAPISpecies *) = 0;
            /**
              * @return Return a list of all the molecules in the box.
              */
            virtual IAPIMoleculeList *getMoleculeList() = 0;
            /**
              * @return Return a list of all the atoms in the box.
              */
            virtual IAPIAtomList *getLeafList() = 0;
            /**
              * @return Return the box's boundary.
              */
            virtual IAPIBoundary *getBoundary() = 0;
            /**
              * Set the box's boundary to the given boundary.
              * @param boundary Box's new boundary.
              */
            virtual void setBoundary(IAPIBoundary *) = 0;
            /**
              * @return Returns the event manager for the box.
              */
            virtual IAPIBoxEventManager *getEventManager() = 0;
            /**
              * Notify the box that a species has been added to the
              * simulation.
              * WARNING : Only the he simulation's species manager should
              *           call this method
              * @param species Species added to the simulation.
              */
            virtual void addSpeciesNotify(IAPISpecies *) = 0;
            /**
              * Notify the box that a species has been removed from the
              * simulation.
              * WARNING : Only the he simulation's species manager should
              *           call this method
              * @param species Species removed from the simulation.
              */
            virtual void removeSpeciesNotify(IAPISpecies *) = 0;

    };
}

#endif
