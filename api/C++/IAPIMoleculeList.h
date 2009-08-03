/*
 *  IAPIMoleculeList.h
 *  API Glue
 *
 */

#ifndef API_IMOLECULELIST_WRAPPER_H
#define API_IMOLECULELIST_WRAPPER_H

#include "IAPIMolecule.h"

namespace molesimAPI
{

    class IAPIMoleculeList {

        public:

            // API Compliance
            virtual int getMoleculeCount() = 0;			
            virtual IAPIMolecule *getMolecule(int) = 0;

    };
}
#endif
