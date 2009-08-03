/*
 *  IAPIAtomList.h
 *  API Glue
 *
 */

#ifndef API_IATOMLIST_WRAPPER_H
#define API_IATOMLIST_WRAPPER_H

#include "IAPIAtom.h"

namespace molesimAPI
{


    class IAPIAtomList {

        public:

            // API Compliance
            virtual int getAtomCount() = 0;			
            virtual IAPIAtom *getAtom(int) = 0;

    };
}
#endif
