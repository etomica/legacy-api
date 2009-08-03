/*
 *  GlotzillaVector2D.h
 *  API Glue
 *
 */

#ifndef GLOTZ_VECTOR2D_WRAPPER_H
#define GLOTZ_VECTOR2D_WRAPPER_H

#include "IAPIVectorMutable.h"
#include "IAPIFunction.h"
#include "GlotzillaVector.h"

using namespace molesimAPI;

namespace glotzwrappers
{

    /**
      * GlotzillaVector2D implements a vector in two dimensional space.
      */
    class GlotzillaVector2D : public GlotzillaVector, public virtual IAPIVectorMutable {

        public:
            /**
              * Creates a 2 dimensional vector that hold a new instance of a
              * native Glotzilla vector (glotzmath::glotz_vec).  The
              * components of the vector are set to 0.
              */
            GlotzillaVector2D();
            /**
              * Creates a 2 dimensional vector that hold a new instance of a
              * native Glotzilla vector (glotzmath::glotz_vec).  The
              * components of the vector are set to the given values except
              * for the 3rd component (Z component), which is set to 0.
              * @param v1 Value to set X-component of this vector.
              * @param v2 Value to set Y-component of this vector.
              */
            GlotzillaVector2D(double v1, double v2);
            /**
              * Creates a 2 dimensional vector that holds the given instance
              * of a native Glotzilla vector (glotzmath::glotz_vec).  The
              * components of the vector are left unchanged (from the values
              * that the native Glotzilla vector holds).
              */
            GlotzillaVector2D(glotzmath::glotz_vec *gVec);
            /**
              * Creates a 2 dimensional vector that hold a new instance of a
              * native Glotzilla vector (glotzmath::glotz_vec).  The
              * components of the vector are set to the values of the given
              * vector except for the 3rd component (Z component), which is
              * set to 0.
              * @param v Vector holding values to set components of this vector.
              */
            GlotzillaVector2D(GlotzillaVector2D *v);
            ~GlotzillaVector2D();

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
            void XE(IAPIVector *f);

    };
}

#endif
