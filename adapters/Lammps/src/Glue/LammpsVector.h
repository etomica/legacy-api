/*
 *  LammpsVector.h
 *  API Glue
 *
 */

#ifndef LAMMPS_VECTOR_WRAPPER_H
#define LAMMPS_VECTOR_WRAPPER_H

#include "IAPIVector.h"
#include "IAPIVectorMutable.h"

using namespace molesimAPI;

namespace lammpswrappers
{

    class LammpsVector : public virtual IAPIVectorMutable {
        public:
            /**
              * The only reason this class exists is a defiency in the
              * parsers that make a java layer over this C++ layer.
              * Really, VERY BAD.
              */
            LammpsVector();

            // API Compliance
            virtual void assignTo(double values[]) = 0;
            virtual int getD() = 0;
            virtual bool equals(IAPIVector *v) = 0;
            virtual double getX(int index) = 0;
            virtual void setX(int index, double value) = 0;
            virtual void E(IAPIVector *v) = 0;
            virtual void E(double d) = 0;
            virtual void E(double d[]) = 0;
            virtual void PE(IAPIVector *v) = 0;
            virtual void PE(double d) = 0;
            virtual void ME(IAPIVector *v) = 0;
            virtual void TE(IAPIVector *v) = 0;
            virtual void TE(double d) = 0;
            virtual void DE(IAPIVector *v) = 0;
            virtual void Ea1Tv1(double d, IAPIVector *v) = 0;
            virtual void PEa1Tv1(double d, IAPIVector *v) = 0;
            virtual void Ev1Pv2(IAPIVector *v1, IAPIVector *v2) = 0;
            virtual void Ev1Mv2(IAPIVector *v1, IAPIVector *v2) = 0;
            virtual void mod(IAPIVector *v) = 0;
            virtual double squared() = 0;
            virtual bool isZero() = 0;
            virtual double dot(IAPIVector *v) = 0;
            virtual bool isNaN() = 0;
            virtual double Mv1Squared(IAPIVector *v) = 0;
            virtual void normalize() = 0;
            virtual void map(IAPIFunction *f) = 0;

        protected:
            int D;
            double *pos;
    };
}

#endif
