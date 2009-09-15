/*
 *  TowheeAtomTypeSphere.h
 *  API Glue
 *
 */

#ifndef TOWHEE_ATOMTYPESPHERE
#define TOWHEE_ATOMTYPESPHERE

#include "IAPIAtomTypeSphere.h"

#include "TowheeAtomType.h"

using namespace molesimAPI;

namespace towheewrappers
{

    class TowheeAtomTypeSphere : public TowheeAtomType,
                                    public virtual IAPIAtomTypeSphere {

        public:

            TowheeAtomTypeSphere(int index);

            void setDiameter(double d);
            double getDiameter();

        private:
            double mDiameter;
    };
}
#endif
