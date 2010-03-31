/*
 *  LammpsVector2D.h
 *  API Glue
 *
 */

#ifndef LAMMPS_VECTOR2D_WRAPPER_H
#define LAMMPS_VECTOR2D_WRAPPER_H

#include "IAPIVector.h"
#include "IAPIVectorMutable.h"
#include "LammpsVector.h"

using namespace molesimAPI;

namespace lammpswrappers
{

    class LammpsVector2D : public LammpsVector, public virtual IAPIVectorMutable {
        public:
            /**
              * Creates a 2 dimensional vector.  The components of the
              * vector are set to 0.
              */
            LammpsVector2D();
            /**
              * Creates a 2 dimensional vector.  The components of the
              * vector are set to the given values.
              * @param v1 Value to set X-component of this vector.
              * @param v2 Value to set Y-component of this vector.
              */
            LammpsVector2D(double v1, double v2);
            /**
              * Creates a 2 dimensional vector.  The components of the
              * vector are set to the given values.
              * @param v Vector holding values to set components of this
              *          vector.
              */
            LammpsVector2D(LammpsVector2D *v);
            /**
              * Creates a 2 dimensional vector.  The vector uses the given
              * double array as its own storage.  That is to say, modifying
              * the vector components modifies the given array values
              * directly.
              * @param v Storage pointer(array) to use.
              */
            LammpsVector2D(double *v);

            // API Compliance
            int getD();
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
            void Ea1Tv1(double d, IAPIVector *v);
            void PEa1Tv1(double d, IAPIVector *v);
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
            void XE(IAPIVector *v);

            // NON-Api methods
            /**
              * Sets the components of this vector equal to those given.
              * @param a This vector's new X Value.
              * @param b This vector's new Y Value.
              */
            void E(double a, double b);

    };
}

#endif
