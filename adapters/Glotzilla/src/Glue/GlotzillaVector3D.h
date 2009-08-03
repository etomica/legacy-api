/*
 *  GlotzillaVector3D.h
 *  API Glue
 *
 */

#ifndef GLOTZ_VECTOR3D_WRAPPER_H
#define GLOTZ_VECTOR3D_WRAPPER_H

#include "IAPIVectorMutable.h"
#include "IAPIFunction.h"
#include "GlotzillaVector.h"

using namespace molesimAPI;

namespace glotzwrappers
{

    /**
      * GlotzillaVector3D implements a vector in three dimensional space.
      */
    class GlotzillaVector3D : public GlotzillaVector,
                              public virtual IAPIVectorMutable {
        public:
            /**
              * Creates a 3 dimensional vector that hold a new instance of a
              * native Glotzilla vector (glotzmath::glotz_vec).  The
              * components of the vector are set to 0.
              */
            GlotzillaVector3D();
            /**
              * Creates a 3 dimensional vector that hold a new instance of a
              * native Glotzilla vector (glotzmath::glotz_vec).  The
              * components of the vector are set to the given values.
              * @param v1 Value to set X-component of this vector.
              * @param v2 Value to set Y-component of this vector.
              * @param v3 Value to set Z-component of this vector.
              */
            GlotzillaVector3D(double v1, double v2, double v3);
            /**
              * Creates a 3 dimensional vector that holds the given instance
              * of a native Glotzilla vector (glotzmath::glotz_vec).  The
              * components of the vector are left unchanged (from the values
              * that the native Glotzilla vector holds).
              */
            GlotzillaVector3D(glotzmath::glotz_vec *gVec);
            /**
              * Creates a 3 dimensional vector that hold a new instance of a
              * native Glotzilla vector (glotzmath::glotz_vec).  The
              * components of the vector are set to the values of the given
              * vector.
              * @param v Vector holding values to set components of this
              *          vector.
              */
            GlotzillaVector3D(GlotzillaVector3D *v);
            ~GlotzillaVector3D();

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
            void XE(IAPIVector *v);
            void E(double a, double b, double c);

            // Non-API methods
            double *make3DArray(double x, double y, double z);


    };
}

#endif
