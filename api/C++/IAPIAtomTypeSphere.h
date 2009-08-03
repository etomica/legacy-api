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
            virtual void setDiameter(double) = 0;
            virtual double getDiameter() = 0;

    };
}
#endif
