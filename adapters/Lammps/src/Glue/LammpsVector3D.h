/*
 *  LammpsVector3D.h
 *  API Glue
 *
 */

#ifndef LAMMPS_VECTOR3D_WRAPPER_H
#define LAMMPS_VECTOR3D_WRAPPER_H

#include "IAPIVectorMutable.h"
#include "IAPIFunction.h"
#include "LammpsVector.h"

using namespace molesimAPI;

namespace lammpswrappers
{

    class LammpsVector3D : public LammpsVector, public virtual IAPIVectorMutable {
        public:
            /**
              * Creates a 3 dimensional vector.  The components of the
              * vector are set to 0.
              */
            LammpsVector3D();
            /**
              * Creates a 3 dimensional vector.  The components of the
              * vector are set to the given values.
              * @param v1 Value to set X-component of this vector.
              * @param v2 Value to set Y-component of this vector.
              * @param v3 Value to set Z-component of this vector.
              */
            LammpsVector3D(double v1, double v2, double v3);
            /**
              * Creates a 3 dimensional vector.  The components of the
              * vector are set to the given values.
              * @param v Vector holding values to set components of this
              *          vector.
              */
            LammpsVector3D(LammpsVector3D *v);
            /**
              * Creates a 3 dimensional vector.  The vector uses the given
              * array as its own storage.  That is to say, modifying the
              *  vector components modifies the given array values directly.
              * @param v Storage pointer(array) to use.
              */
            LammpsVector3D(double *v);

            // API Compliance
            void assignTo(double values[]);
            int getD();
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

            // Non-API methods
            /**
              * Sets the components of this vector equal to those given.
              * @param a This vector's new X Value.
              * @param b This vector's new Y Value.
              * @param c This vector's new Z Value.
              */
            void E(double a, double b, double c);
            /**
              * Makes (allocates memory) for a 3D array, populates the array
              * with the component values of this vector and returns the
              * array.
              * @return Returns the pointer(array) as described above.
              */
            double *make3DArray(double x, double y, double z);

    };
}

#endif
