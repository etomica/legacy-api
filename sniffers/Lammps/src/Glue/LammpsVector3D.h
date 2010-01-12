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

namespace lammpssnifferwrappers
{

    class LammpsVector3D : public LammpsVector, public virtual IAPIVectorMutable {
        public:
            LammpsVector3D();
//            LammpsVector3D(double v1, double v2, double v3);
//            LammpsVector3D(LammpsVector3D *v);
            LammpsVector3D(double **v);

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
            void E(double a, double b, double c);
            double *make3DArray(double x, double y, double z);

    };
}

#endif
