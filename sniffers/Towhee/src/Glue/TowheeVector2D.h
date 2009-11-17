/*
 *  TowheeVector2D.h
 *  API Glue
 *
 */

#ifndef TOWHEE_VECTOR2D_WRAPPER_H
#define TOWHEE_VECTOR2D_WRAPPER_H

#include "IAPIVectorMutable.h"
#include "IAPIFunction.h"
#include "TowheeVector.h"

using namespace molesimAPI;

namespace towheesnifferwrappers
{

    /**
      * TowheeVector2D implements a vector in two dimensional space.
      */
    class TowheeVector2D : public TowheeVector, public virtual IAPIVectorMutable {

        public:
            // API Compliance
            void assignTo(double values[]);
            bool equals(IAPIVector *v);
            double getX(int index);
            void setX(int index, double value);
            void E(IAPIVector *v);
            void E(double d);
            void E(double d[]);
            void PE(IAPIVector *v);
            void PE(double d);
            void ME(IAPIVector *v);
            void TE(IAPIVector *v);
            void TE(double d);
            void DE(IAPIVector *v);
            void Ea1Tv1(double d, IAPIVector *v1);
            void PEa1Tv1(double d, IAPIVector *v1);
            void Ev1Pv2(IAPIVector *v1, IAPIVector *v2);
            void Ev1Mv2(IAPIVector *v1, IAPIVector *v2);
            void mod(IAPIVector *v);
            double squared();
            bool isZero();
            double dot(IAPIVector *v);
            bool isNaN();
            double Mv1Squared(IAPIVector *v);
            void normalize();
            void map(IAPIFunction *f);
            void XE(IAPIVector *f);

    };
}

#endif
