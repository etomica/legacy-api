/*
 *  TowheeVector3DAtom.h
 *  API Glue
 *
 */

#ifndef TOWHEE_VECTOR3D_ATOM_WRAPPER_H
#define TOWHEE_VECTOR3D_ATOM_WRAPPER_H

#include "IAPIVectorMutable.h"
#include "IAPIAtom.h"
#include "TowheeVector3D.h"

using namespace molesimAPI;

namespace towheesnifferwrappers
{

    class TowheeAtom;

    class TowheeVector3DAtom : public TowheeVector3D {
        public:

            TowheeVector3DAtom(TowheeAtom *atom,
                               void (*fnct)(int *, int *, int *, int *, double *, double *, double *),
                                   int ia1, int ia3);

            // API Compliance
            void assignTo(double values[]);
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
            void XE(IAPIVector *v);
            void E(double a, double b, double c);

            // Non-API methods
            void update();

        private:
            void setAll();
            IAPIVector *getOffset();
            void (*mFunction)(int *, int *, int *, int *, double *, double *, double *);
            int iArg1;
            int iArg3;
            TowheeAtom *mAtom;
    };
}

#endif
