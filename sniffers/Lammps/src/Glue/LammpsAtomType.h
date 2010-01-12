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

namespace lammpssnifferwrappers
{

    class LammpsAtomType : public virtual IAPIAtomType {

        public:
            LammpsAtomType();
            LammpsAtomType(double m);
            LammpsAtomType(int at);
            LammpsAtomType(int at, double m);

            // API Compliance : IAPIAtomType
            void setIndex(int index);
            int getIndex();
            void setSpecies(IAPISpecies *newParent);
            IAPISpecies *getSpecies();
            void setChildIndex(int newChildIndex);
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
