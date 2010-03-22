/*
 *  LammpsAtomType.h
 *  API Glue
 *
 */

#ifndef LAMMPS_ATOMTYPE_WRAPPER_H
#define LAMMPS_ATOMTYPE_WRAPPER_H

#include "IAPIAtomType.h"
#include "IAPIElement.h"
#include "IAPISpecies.h"

using namespace molesimAPI;

namespace lammpswrappers
{

    class LammpsAtomType : public virtual IAPIAtomType {

        public:
            /**
              * Create an atom type.  The atom type will have its index
              * set to 0 and its mass set to 1.0.
              */ 
            LammpsAtomType();
            /**
              * Create an atom type.  The atom type will have its index
              * set to 0 and mass set to the values passed in.
              * @param m the atom type's mass
              */
            LammpsAtomType(double m);
            /**
              * Create an atom type.  The atom type will have its index
              * set to the value passed in and its mass set to 1.0.
              * @param at the atom type's index
              */ 
            LammpsAtomType(int at);
            /**
              * Create an atom type.  The atom type will have its index
              * and mass set to the values passed in.
              * @param at the atom type's index
              * @param m the atom type's mass
              */
            LammpsAtomType(int at, double m);

            // API Compliance : IAPIAtomType
            void setIndex(int index);
            int getIndex();
            void setSpecies(IAPISpecies *newParent);
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

        private:
            IAPISpecies *mSpecies;
            double       mMass;
            int mAtomType;
            static const double DEFAULT_MASS;
            static const int DEFAULT_TYPE;
    };
}
#endif
