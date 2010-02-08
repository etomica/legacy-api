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

namespace lammpssnifferwrappers
{

    class LammpsVector2D : public LammpsVector, public virtual IAPIVectorMutable {
        public:
            LammpsVector2D();
//            LammpsVector2D(double v1, double v2);
//            LammpsVector2D(LammpsVector2D *v);
            LammpsVector2D(double **v);

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
            void E(double a, double b);

    };
}

#endif
