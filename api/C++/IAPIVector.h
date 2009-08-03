/*
 *  IAPIVector.h
 *  API Glue
 *
 */

#ifndef API_IVECTOR_WRAPPER_H
#define API_IVECTOR_WRAPPER_H

#include "IAPIFunction.h"

namespace molesimAPI
{
    class IAPIVector {

        public:
            virtual void assignTo(double values[]) = 0;
            virtual int getD() = 0;
            virtual bool equals(IAPIVector *) = 0;
            virtual double getX(int) = 0;
            virtual double squared() = 0;
            virtual bool isZero() = 0;
            virtual double dot(IAPIVector *) = 0;
            virtual bool isNaN() = 0;
            virtual double Mv1Squared(IAPIVector *) = 0;

    };
}

#endif
