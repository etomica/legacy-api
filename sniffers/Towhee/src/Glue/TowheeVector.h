/*
 *  TowheeVector.h
 *  API Glue
 *
 */

#ifndef TOWHEE_VECTOR_WRAPPER_H
#define TOWHEE_VECTOR_WRAPPER_H

#include "IAPIVectorMutable.h"
#include "IAPIFunction.h"

using namespace molesimAPI;

namespace towheesnifferwrappers
{

    class TowheeVector : public virtual IAPIVectorMutable {

        public:
            TowheeVector();

            // API Compliance
            /**
              * Assigns the components of this vector to the elements of the
              * given array.
              * @param values array to assign vector value to
              */
            virtual void assignTo(double values[]) = 0;
            /**
              * @return Returns the dimension of the vector
              */
            virtual int getD();
            /**
              * Compares this vector with the given vector.
              * @param v Vector to compare this vector to.
              * @return Returns true if all of the elements of this vector
              *         are the same as the elements of the given vector.
              */
            virtual bool equals(IAPIVector *v) = 0;
            /**
              * @param index Dimension to return vector's value
              *              (x = 0, Y = 1, Z = 2).
              * @return Returns the i-th componenet of the vector.
              */
            virtual double getX(int index) = 0;
            /**
              * Sets the i-th component of the vector to the given value.
              * @param index The vector's componenet number
              *              (X = 0, Y = 1, Z = 2).
              * @param value Set the vector's componenet to this value.
              */
            virtual void setX(int index, double value) = 0;
            /**
              * Sets the components of this vector equal to those of the
              * given vector.
              * @param v Vector to get values from.
              */
            virtual void E(IAPIVector *v) = 0;
            /**
              * Sets all of the components of this vector equal to the value
              * given.
              * @param d Value to set this vector's componenets to.
              */
            virtual void E(double d) = 0;
            /**
              * Sets the components of this vector equal to those of the
              * given array.
              * @param d Array of value to set this vector's componenets to.
              *          (X = d[0], Y = d[1], Z = d[2]).
              */
            virtual void E(double d[]) = 0;
            /**
              * Plus-equals (+=) operation. Increments each component of this
              * vector by the corresponding value in the given vector.
              * @param v Vector to get incremental values from.
              */
            virtual void PE(IAPIVector *v) = 0;
            /**
              * Plus-equals (+=) operation. Increments each component of this
              * vector by the given value.
              * @param d  to get incremental values from.
              * @param d Value to use as incremental value.
              */
            virtual void PE(double d) = 0;
            /**
              * Minus-equals (+=) operation. Decrements each component of
              * this vector by the corresponding value in the given vector.
              * @param v Vector to get decremental values from.
              */
            virtual void ME(IAPIVector *v) = 0;
            /**
              * Times-equals (+=) operation. Multiplies each component of
              * this vector by the corresponding value in the given vector.
              * @param v Vector to get multiplication factors from.
              */
            virtual void TE(IAPIVector *v) = 0;
            /**
              * Times-equals (+=) operation. Multiplies each component of
              * this vector by the given value.
              * @param d Value to use as multiplication factor.
              */
            virtual void TE(double d) = 0;
            /**
              * Divide-equals (+=) operation. Divides each component of
              * this vector by the corresponding value in the given vector.
              * @param v Vector to get division factors from.
              */
            virtual void DE(IAPIVector *v) = 0;
            /**
              * Operation (a1 * v1). Sets this vector's component values
              * equal to the values of the vector given multiplied by the
              * given constant.
              * @param d Constant value.
              * @param v Vector to be multiplied by constant.
              */
            virtual void Ea1Tv1(double d, IAPIVector *v1) = 0;
            /**
              * Operation (+= a1 * v1). Add to this vector's component values
              * the values of the given vector multiplied by the given
              * constant.
              * @param d Constant value.
              * @param v Vector to be multiplied by constant.
              */
            virtual void PEa1Tv1(double d, IAPIVector *v1) = 0;
            /**
              * Operation (v1 + v2). Sets this vector equal to the value
              * of adding the two given vectors.
              * @param v1 One of the vectors to add together
              * @param v2 One of the vectors to add together
              */
            virtual void Ev1Pv2(IAPIVector *v1, IAPIVector *v2) = 0;
            /**
              * Operation (v1 - v2). Sets this vector equal to the value
              * of subtracting the second given vector from the first given
              * vector.
              * @param v1 Vector to subtract from.
              * @param v2 Vector to subtract.
              */
            virtual void Ev1Mv2(IAPIVector *v1, IAPIVector *v2) = 0;
            /**
              * Replaces each component of this vector with its value modulo
              * determined by dividing by the given vector..
              * @param v Vector to divide this vector by to get modulo.
              */
            virtual void mod(IAPIVector *v) = 0;
            /**
              * @return Returns the value of squaring each of the vector's
              *         components and adding those components together.
              */
            virtual double squared() = 0;
            /**
              * @return Returns true if all components of this vector are
              *         zero; false otherwise.
              */
            virtual bool isZero() = 0;
            /**
              * @param v Vector to use in computing dot product.
              * @return Returns the dot product of this vector with the
              *         given one.
              */
            virtual double dot(IAPIVector *v) = 0;
            /**
              * @return Returns true if any element of the vector is
              *         not-a-number.
              */
            virtual bool isNaN() = 0;
            /**
              * @param Vector to subtract from this vector.
              * @return Returns square of vector resulting from subtracting
              *         given vector from this one.  Neither vector is
              *         changed by this operation.
              */
            virtual double Mv1Squared(IAPIVector *v) = 0;
            /**
              * Normalizes this vector, so this.squared() == 1.  Divides all 
              * components by Math.sqrt(this.squared()).
              */
            virtual void normalize() = 0;
            /**
              * Applies the given function to each element of the vector.
              * @param f Function to apply to this vector.
              */
            virtual void map(IAPIFunction *f) = 0;

        protected:
            int D;

    };
}

#endif
