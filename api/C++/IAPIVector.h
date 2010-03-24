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
            /**
              * Assigns the components of this vector to the elements of the
              * given array.  Does not check that array length is consistent
              * with vector dimension.  Inverse of the E method.
              * @param values Array that will be assigned the values, in each
              *               dimension, of the vector.
              */
            virtual void assignTo(double values[]) = 0;
            /**
              * @return Returns the dimension of the space occupied by the
              *         vector. Number of elements in the vector.
              */
            virtual int getD() = 0;
            /**
              * @param v Vector to compare this vector to.
              * @return Returns true if all corresponding elements of this
              *         vector and the given vector are equal; returns false
              *         otherwise.
              */
            virtual bool equals(IAPIVector *v) = 0;
            /**
              * @param i Index of dimension to return vector component.
              * @return Returns the vector component for the dimension
              *         corresponding to the given index.
              */
            virtual double getX(int i) = 0;
            /**
              * @return Returns the square magnitude of this vector.
              *         e.g., x^2 + y^2 for D = 2.
              */
            virtual double squared() = 0;
            /**
              * @return Returns true if all components of this vector are
              *         zero; false otherwise.
              */
            virtual bool isZero() = 0;
            /**
              * @param v Vector to use with this vector when computing dot
              *          product.
              * @return Returns the dot product of this vector with the given
              *         one.
              */
            virtual double dot(IAPIVector *v) = 0;
            /**
              * @return Returns true if any element of the vector is
              *         not-a-number.
              */
            virtual bool isNaN() = 0;
            /**
              * @param v Vector to subtract before computing square of
              *          of this vector.
              * @return Returns square of vector resulting from subtracting
              *         given vector from this one.  Neither vector is
              *         changed by this operation.
              */
            virtual double Mv1Squared(IAPIVector *v) = 0;

    };
}

#endif
