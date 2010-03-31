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
            /**
              * Create an atom type sphere.  The diameter of the sphere will
              * be set to 1.0.
              */
            LammpsAtomTypeSphere();
            /**
              * Create an atom type sphere.  The diameter of the sphere will
              * be set to 1.0.
              * @param mass the atom type's mass
              */
            LammpsAtomTypeSphere(double mass);
            /**
              * Create an atom type sphere.  The diameter of the sphere will
              * be set to 1.0.
              * @param at the atom type's index
              */
            LammpsAtomTypeSphere(int at);
            /**
              * Create an atom type sphere.  The diameter of the sphere will
              * be set to 1.0.
              * @param at the atom type's index
              * @param mass the atom type's mass
              */
            LammpsAtomTypeSphere(int at, double mass);

            // API Compliance
            void setDiameter(double d);
            double getDiameter();

        private:
            double diameter;

    };
}
#endif
