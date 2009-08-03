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
          virtual double getRange() = 0;
          virtual void setBox(IAPIBox *) = 0;
          virtual int nBody() = 0;
    };

}
#endif
