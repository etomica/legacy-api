/*
 *  LammpsAtomType.h
 *  API Glue
 *
 */

#ifndef LAMMPS_ATOMTYPE_WRAPPER_H
#define LAMMPS_ATOMTYPE_WRAPPER_H

#include "IAPIAtomTypeSphere.h"
#include "IAPIElement.h"
#include "IAPISpecies.h"

using namespace molesimAPI;

namespace lammpssnifferwrappers
{

    class LammpsAtomType : public virtual IAPIAtomTypeSphere {

        public:
            LammpsAtomType(int at, int nIndex);
            LammpsAtomType(int at, int nIndex, double m);

            // API Compliance
            void setIndex(int index);
            int getIndex();
            void setSpecies(IAPISpecies *newParent);
            IAPISpecies *getSpecies();
            void setChildIndex(int newChildIndex);
            int getChildIndex();
            double getMass();
            double rm();
            IAPIElement *getElement();
            void setDiameter(double d);
            double getDiameter();

            // Non-API
            int getNativeIndex();

        protected:
            IAPIElement *mElement;

        private:
            IAPISpecies *mSpecies;
            double       mMass;
            int mAtomType;
            double mDiameter;
            int nativeIndex;
            static const double DEFAULT_MASS;
            static const double DEFAULT_DIAMETER;
            static const int DEFAULT_TYPE;
    };
}
#endif
