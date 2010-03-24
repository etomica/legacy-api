/*
 *  IAPIPotential.h
 *  API Glue
 *
 */

#ifndef API_IPOTENTIAL_WRAPPER_H
#define API_IPOTENTIAL_WRAPPER_H

#include "IAPIBox.h"

namespace molesimAPI
{

    class IAPIPotential {

        public:
            /**
              * @return Returns the range over which the potential applies.
              *         Atoms with a greater separation do not interact.
              */
            virtual double getRange() = 0;
            /**
              * Informs the potential of the box on which it acts so that it
              * can properly consider the boundaries.
              * @param box The box on which this potential acts.
              */
            virtual void setBox(IAPIBox *) = 0;
            /**
              * @return Returns the number of atoms on which the potential
              *         depends.
              */
            virtual int nBody() = 0;
    };

}
#endif
