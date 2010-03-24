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
            virtual ~IAPIVectorMutable() {};

            /**
              * Sets the i-th component of the vector to the given value d.
              * If the given index exceeds dimension of vector, no error is
              * given and the last element of the vector is assigned.
              * @param i Dimension of vector to change.
              * @param d Value to set vector component to.
              */
            virtual void setX(int i, double d) = 0;
            /**
              * Sets the components of this vector equal to those of the
              * given vector.
              * @param v Given vector
              */
            virtual void E(IAPIVector *v) = 0;
            /**
              * Sets all components of this vector equal to the given value.
              * @param d given value
              */
            virtual void E(double d) = 0;
            /**
              * Sets all components of this vector equal to the
              * corresponding elements of the given array.
              * @param d given array
              */
            virtual void E(double d[]) = 0;
            /**
              * Plus-equals (+=) operation. Increments each component of this
              * vector by the corresponding value in the given vector.
              * @param v given vector
              */
            virtual void PE(IAPIVector *v) = 0;
            /**
              * Plus-equals (+=) operation. Increments each component of this
              * vector by the given value.
              * @param d given value
              */
            virtual void PE(double d) = 0;
            /**
              * Minus-equals (-=) operation. Decrements each component of
              * this vector by the corresponding value in the given vector.
              * @param v Given vector.
              */
            virtual void ME(IAPIVector *v) = 0;
            /**
              * Times-equals (-=) operation. Multiplies each component of
              * this vector by the corresponding value in the given vector.
              * @param v Given vector.
              */
            virtual void TE(IAPIVector *v) = 0;
            /**
              * Divide-equals (-=) operation. Divides each component of
              * this vector by the corresponding value in the given vector.
              * @param v Given vector.
              */
            virtual void DE(IAPIVector *v) = 0;
            /**
              * Times-equals (-=) operation. Multiplies each component of
              * this vector by the given value.
              * @param d Given value.
              */
            virtual void TE(double d) = 0;
            /**
              * Operation (= a1 * v1); sets the components of this to those
              * of the given vector multiplied by the given constant.
              * @param d given constant
              * @param d given vector
              */
            virtual void Ea1Tv1(double d, IAPIVector *v) = 0;
            /**
              * Increments (+=); increments the components of this to those
              * of the given vector multiplied by the given constant.
              * @param d given constant
              * @param d given vector
              */
            virtual void PEa1Tv1(double d, IAPIVector *v) = 0;
            /**
              * Sets the components of this vector equal to (v1 + v2)
              * @param v1 First of two vectors to be added together.
              * @param v2 Second of two vectors to be added together.
              */
            virtual void Ev1Pv2(IAPIVector *v1, IAPIVector *v2) = 0;
            /**
              * Sets the components of this vector equal to (v1 - v2)
              * @param v1 Vector to be subtracted from.
              * @param v2 Vector to be subtracted.
              */
            virtual void Ev1Mv2(IAPIVector *v1, IAPIVector *v2) = 0;
            /**
              * Replaces each component of this vector with its value modulo.
              * @param v Divisor for modulo computation.
              */
            virtual void mod(IAPIVector *v) = 0;
            /**
              * Normalizes this vector, so this.squared() == 1.  Divides all
              * components by Math.sqrt(this.squared()).
              */
            virtual void normalize() = 0;
            /**
              * Applies the given function to each element of the vector.
              * @param f Given function.
              */
            virtual void map(IAPIFunction *f) = 0;
            /**
              * Sets this vector equal to the cross product of this vector
              * with the given vector (only works for 3D vectors).
              * @param v Given vector.
              */
            virtual void XE(IAPIVector *v) = 0;

    };
}

#endif
