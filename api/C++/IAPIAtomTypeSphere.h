/*
 *  IAPIAtomTypeSphere.h
 *  API Glue
 *
 */

#ifndef API_IATOMTYPESPHERE_WRAPPER_H
#define API_IATOMTYPESPHERE_WRAPPER_H

#include "IAPIAtomType.h"

namespace molesimAPI
{

    class IAPIAtomTypeSphere : public virtual IAPIAtomType {

        public:
            /**
              * Set the diameter of the sphere for all atoms of this type.
              * @param d diameter of sphere
              */
            virtual void setDiameter(double d) = 0;
            /**
              * @return Returns the diameter of the sphere.
              */
            virtual double getDiameter() = 0;

    };
}
#endif
