/*
 *  LammpsAtomTypeSphere.h
 *  API Glue
 *
 */

#ifndef LAMMPS_ATOMTYPESPHERE
#define LAMMPS_ATOMTYPESPHERE

#include "IAPIAtomTypeSphere.h"
#include "LammpsAtomType.h"

using namespace molesimAPI;

namespace lammpswrappers
{

    class LammpsAtomTypeSphere : public LammpsAtomType, public virtual IAPIAtomTypeSphere {

        public:
            LammpsAtomTypeSphere();
            LammpsAtomTypeSphere(double mass);
            LammpsAtomTypeSphere(int at);
            LammpsAtomTypeSphere(int at, double mass);

            // API Compliance : IAPIAtomType
            void setDiameter(double d);
            double getDiameter();

        private:
            double diameter;

    };
}
#endif
