/*
 *  IAPIVectorMutable.h
 *  API Glue
 *
 */

#ifndef API_IVECTOR_MUTABLE_WRAPPER_H
#define API_IVECTOR_MUTABLE_WRAPPER_H

#include "IAPIFunction.h"
#include "IAPIVector.h"

namespace molesimAPI
{
    class IAPIVectorMutable : public virtual IAPIVector {

        public:
            virtual void setX(int, double) = 0;
            virtual void E(IAPIVector *) = 0;
            virtual void E(double) = 0;
            virtual void E(double[]) = 0;
            virtual void PE(IAPIVector *) = 0;
            virtual void PE(double) = 0;
            virtual void ME(IAPIVector *) = 0;
            virtual void TE(IAPIVector *) = 0;
            virtual void DE(IAPIVector *) = 0;
            virtual void TE(double) = 0;
            virtual void Ea1Tv1(double, IAPIVector *) = 0;
            virtual void PEa1Tv1(double, IAPIVector *) = 0;
            virtual void Ev1Pv2(IAPIVector *, IAPIVector *) = 0;
            virtual void Ev1Mv2(IAPIVector *, IAPIVector *) = 0;
            virtual void mod(IAPIVector *) = 0;
            virtual void normalize() = 0;
            virtual void map(IAPIFunction *) = 0;
            virtual void XE(IAPIVector *) = 0;

    };
}

#endif
