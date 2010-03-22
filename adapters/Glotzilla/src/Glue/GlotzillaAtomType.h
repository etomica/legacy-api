/*
 *  GlotzillaAtomType
 *  API Glue
 *
 */

#ifndef GLOTZ_ATOMTYPE_WRAPPER_H
#define GLOTZ_ATOMTYPE_WRAPPER_H

#include "IAPIAtomType.h"
#include "IAPIElement.h"
#include "IAPISpecies.h"

using namespace molesimAPI;

namespace glotzwrappers
{

    /**
      * GlotzillaAtomType hold properties in common with other atoms of the
      * same type.  It hold's an atom's mass and the species that created
      * the atom.
      */
    class GlotzillaAtomType : public virtual IAPIAtomType {

        public:
            /**
              * Create an atom type.  The atom type will have its index
              * set to 0 and its mass set to 1.0.
              */
            GlotzillaAtomType();
            /**
              * Create an atom type.  The atom type will have its index
              * set to the value passed in and its mass set to 1.0.
              * @param at the atom type's index
              */
            GlotzillaAtomType(int at);
            /**
              * Create an atom type.  The atom type will have its index
              * and mass set to the values passed in.
              * @param at the atom type's index
              * @param mass the atom type's mass
              */
            GlotzillaAtomType(int at, double mass);

            // API Compliance
            void setIndex(int newIndex);
            int getIndex();
            void setSpecies(IAPISpecies *newParent);
            IAPISpecies *getSpecies();
            void setChildIndex(int newChildIndex);
            int getChildIndex();
            /**
              * @return Returns the value of the mass for the atom type.
              */
            double getMass();
            /**
              * @return Returns the reciprocal of the mass (1.0/mass) for the
              *         atom type.
              */
            double rm();
            /**
              * @return Returns the element type for the atom type.
              */
            IAPIElement *getElement();

        protected:
            int mAtomType;
            int childIndex;
            IAPIElement *mElement;

        private:
            IAPISpecies *species;
            double mMass;
    };
}
#endif
