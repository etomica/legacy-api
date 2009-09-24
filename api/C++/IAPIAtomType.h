/*
 *  IAPIAtomType.h
 *  API Glue
 *
 */

#ifndef API_IATOMTYPE_WRAPPER_H
#define API_IATOMTYPE_WRAPPER_H

#include "IAPIElement.h"

namespace molesimAPI
{

    class IAPISpecies;

    class IAPIAtomType {

        public:
            virtual void setIndex(int) = 0;
            virtual int getIndex() = 0;
            virtual void setSpecies(IAPISpecies *) = 0;
            virtual void setChildIndex(int) = 0;
            virtual int getChildIndex() = 0;
            virtual IAPISpecies *getSpecies() = 0;
            virtual double getMass() = 0;
            virtual double rm() = 0;
            virtual IAPIElement *getElement() = 0;
    };
}
#endif
