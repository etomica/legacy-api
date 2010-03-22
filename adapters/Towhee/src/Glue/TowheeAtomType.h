/*
 *  TowheeAtomType
 *  API Glue
 *
 */

#ifndef TOWHEE_ATOMTYPE_WRAPPER_H
#define TOWHEE_ATOMTYPE_WRAPPER_H

#include "IAPIAtomType.h"
#include "IAPIElement.h"
#include "IAPISpecies.h"

using namespace molesimAPI;

namespace towheewrappers
{

    class TowheeAtomType : public virtual IAPIAtomType {

        public:
            /**
              * Create an atom type.  The atom type will have its index
              * set to the value passed in and its mass set to 1.0.
              * @param index the atom type's index
              */
            TowheeAtomType(int index);
            /**
              * Create an atom type.  The atom type will have its index
              * and mass set to the values passed in.
              * @param index the atom type's index
              * @param mass the atom type's mass
              */
            TowheeAtomType(int index, double mass);

            void setIndex(int newIndex);
            int getIndex();
            /**
              * This method is not implemented.
              */
            void setSpecies(IAPISpecies *newParent);
            /**
              * This method is not implemented.
              */
            IAPISpecies *getSpecies();
            /**
              * This method is not implemented.
              */
            void setChildIndex(int newChildIndex);
            /**
              * This method is not implemented.
              */
            int getChildIndex();
            double getMass();
            double rm();
            IAPIElement *getElement();

        protected:
            IAPIElement *mElement;

        private :
            /**
              * Sets the index (see setIndex) of the atom type and sets the
              * mass of the atom in the native Towhee simulation (twh_mass).
              * @param index index (see setIndex) of the atom type
              * @param m mass associated to the atom type
              */
            void setup(int index, double m);
            int mIndex;
    };
}
#endif
