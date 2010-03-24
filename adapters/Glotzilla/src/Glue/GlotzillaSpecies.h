/*
 *  GlotzillaSpecies.h
 *  API Glue
 *
 */

#ifndef GLOTZ_SPECIES_WRAPPER_H
#define GLOTZ_SPECIES_WRAPPER_H

#include "jni.h"

#include "IAPISpecies.h"
#include "IAPIAtomType.h"
#include "IAPIMolecule.h"
#include "IAPISimulation.h"
#include "GlotzillaInterfaceConformation.h"
#include "GlotzillaSimulation.h"

#include <vector>

using namespace molesimAPI;

namespace glotzwrappers
{

    /**
      * @todo Description of GlotzillaSpecies here.
      */
    class GlotzillaSpecies : public virtual IAPISpecies {

        public:

            /**
              * Constructor for the species.  The class is purely
              * virtual and the constructor is only called by its
              * subclasses.
              * @param sim Simulations that the species belongs to.
              * @param conform The species conformation.
              * @param pd The species atom position definition.
              */
            GlotzillaSpecies(IAPISimulation *sim,
                             GlotzillaInterfaceConformation *conform);
            // API compliant methods
            virtual int getIndex();
            virtual void setIndex(int index);
            virtual IAPIMolecule *makeMolecule() = 0;
            int getAtomTypeCount();
            IAPIAtomType *getAtomType(int index);
            void initializeConformation(IAPIMolecule *molecule);

            // Non-API methods
            /**
              * Add an atom type to the species atom type list used for
              * molecule creation.
              * @param type atom type to add to list.
              */
            virtual void addChildType(IAPIAtomType *type);
            /**
              * Remove an atom type from the species atom type list used for
              * molecule creation.
              * @param type atom type to remove from list.
              * @todo Current implementation checks atom type's index an
              *       removes from list if index matches.  Removes all atom
              *       types from list with same index.  What should really be
              *       removed is to complare pointers and remove if pointer
              *       is the same.
              */
            void removeChildType(IAPIAtomType *type);

        protected:
            GlotzillaInterfaceConformation *mConformation;
            std::vector<IAPIAtomType *> typeList;
            GlotzillaSimulation *mSim;

        private:
            int mIndex;
    };
}

#endif
