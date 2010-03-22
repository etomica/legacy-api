/*
 *  IAPIAtomType.h
 *  API Glue
 *
 */

#ifndef API_IATOMTYPE_WRAPPER_H
#define API_IATOMTYPE_WRAPPER_H

#include "IAPIElement.h"

namespace molesimAPI
{

    class IAPISpecies;

    /**
      * IAPIAtomType hold properties in common with other atoms of the
      * same type.  It hold's an atom's mass and the species that created
      * the atom.
      */
    class IAPIAtomType {

        public:
            /**
              * Set the atom type's index.  The index is a number that
              * indicates its position in the simulation's atom type list.
              * @param newIndex atom types index
              */
            virtual void setIndex(int newIndex) = 0;
            /**
              * Get the atom type's index.  The index is a number that
              * indicates its position in the simulation's atom type list.
              * @return atom type's index
              */
            virtual int getIndex() = 0;
            /**
              * Set the species that created the atom type.  In effect, the
              * species that created the atom type is the atom type's
              * parent.
              * @param newParent species that created the atom type
              */
            virtual void setSpecies(IAPISpecies *newParent) = 0;
            /**
              * Set the atom type's child index.  The child index is a number
              * that indicates its position in its parent species atom type
              * list.
              * @param newIndex atom types index
              */
            virtual void setChildIndex(int newIndex) = 0;
            /**
              * Gets the atom type's child index.  The index is a number
              * that indicates its position in its parents (Species) atom
              * type list.
              * @return atom type's child index
              */
            virtual int getChildIndex() = 0;
            /**
              * @return the species that created the atom type.
              */
            virtual IAPISpecies *getSpecies() = 0;
            /**
              * @return Returns the value of the mass for the atom type.
              */
            virtual double getMass() = 0;
            /**
              * @return Returns the reciprocal of the mass (1.0/mass) for the
              *         atom type.
              */
            virtual double rm() = 0;
            /**
              * @return Returns the element type for the atom type.
              */
            virtual IAPIElement *getElement() = 0;
    };
}
#endif
