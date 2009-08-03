/*
 *  GlotzillaAtomTypeSphere.h
 *  API Glue
 *
 */

#ifndef GLOTZ_ATOMTYPESPHERE
#define GLOTZ_ATOMTYPESPHERE

#include "IAPIAtomTypeSphere.h"

#include "GlotzillaAtomType.h"

using namespace molesimAPI;

namespace glotzwrappers
{

    /**
      * GlotzillaAtomTypeSphere holds an atom's diameter.
      */
    class GlotzillaAtomTypeSphere : public GlotzillaAtomType,
                                    public virtual IAPIAtomTypeSphere {

        public:
            /**
              * Create an atom type sphere.  The diameter of the sphere will
              * be set to 0.
              */
            GlotzillaAtomTypeSphere();
            /**
              * Create an atom type sphere.  The diameter of the sphere will
              * be set to 0.
              */
            GlotzillaAtomTypeSphere(int at);
            /**
              * Create an atom type sphere.  The diameter of the sphere will
              * be set to 0.
              */
            GlotzillaAtomTypeSphere(int at, double mass);

            // API Compliance
            /**
              * Set the diameter of the sphere for all atoms of this type.
              * @param d diameter of sphere
              */
            void setDiameter(double d);
            /**
              * @return Returns the diamter of the sphere.
              */
            double getDiameter();

        private:
            double diameter;

    };
}
#endif
