/*
 *  TowheeVector3DAtom.cpp
 *  API Glue
 *
 */

#include "stdio.h"

#include "preproc.h"

#include "TowheeVector3DAtom.h"

namespace towheewrappers
{

    TowheeVector3DAtom::TowheeVector3DAtom(void (*fnct)(int *, int *, int *, int *, double *, double *, double *), int ia1, int ia2, int ia3, IAPIVector *offsetVector) {
        mFunction = fnct;
        iArg1 = ia1;
        iArg2 = ia2;
        iArg3 = ia3;
        offset = offsetVector;
    }

    /*
     * assignTo
     */
    void TowheeVector3DAtom::assignTo(double values[]) {
        TowheeVector3D::assignTo(values);
        values[0] -= offset->getX(0);
        values[1] -= offset->getX(1);
        values[2] -= offset->getX(2);
    }

    /*
     * getX
     */
    double TowheeVector3DAtom::getX(int index) {
        int get = GLB_GET;
        (*mFunction)(&get, &iArg1, &iArg2, &iArg3, &vecPos[0], &vecPos[1], &vecPos[2]);
        return vecPos[index]-offset->getX(index);
    }

    /*
     * setX
     */
    void TowheeVector3DAtom::setX(int index, double value) {
        TowheeVector3D::setX(index, value);
        vecPos[index] += offset->getX(index);
        int set = GLB_SET;
        (*mFunction)(&set, &iArg1, &iArg2, &iArg3, &vecPos[0], &vecPos[1], &vecPos[2]);
    }

    /*
     * setAll
     */
    void TowheeVector3DAtom::setAll() {
        int set = GLB_SET;
        (*mFunction)(&set, &iArg1, &iArg2, &iArg3, &vecPos[0], &vecPos[1], &vecPos[2]);
    }

    /*
     * update
     */
    void TowheeVector3DAtom::update() {
        int get = GLB_GET;
        (*mFunction)(&get, &iArg1, &iArg2, &iArg3, &vecPos[0], &vecPos[1], &vecPos[2]);
    }

    /*
     * E
     */
    void TowheeVector3DAtom::E(IAPIVector *v) {
        TowheeVector3D::E(v);
        setAll();
    }

    /*
     * E
     */
    void TowheeVector3DAtom::E(double d) {
        TowheeVector3D::E(d);
        setAll();
    }

    /*
     * E
     */
    void TowheeVector3DAtom::E(double d[]) {
        TowheeVector3D::E(d);
        setAll();
    }

    /*
     * PE
     */
    void TowheeVector3DAtom::PE(IAPIVector *v) {
        TowheeVector3D::PE(v);
        setAll();
    }

    /*
     * PE
     */
    void TowheeVector3DAtom::PE(double d) {
        TowheeVector3D::PE(d);
        setAll();
    }

    /*
     * ME
     */
    void TowheeVector3DAtom::ME(IAPIVector *v) {
        TowheeVector3D::ME(v);
        setAll();
    }

    /*
     * TE
     */
    void TowheeVector3DAtom::TE(IAPIVector *v) {
        TowheeVector3D::TE(v);
        setAll();
    }

    /*
     * TE
     */
    void TowheeVector3DAtom::TE(double d) {
        TowheeVector3D::TE(d);
        setAll();
    }

    /*
     * DE
     */
    void TowheeVector3DAtom::DE(IAPIVector *v) {
        TowheeVector3D::DE(v);
        setAll();
    }

    /*
     * Ea1Tv1
     */
    void TowheeVector3DAtom::Ea1Tv1(double d, IAPIVector *v) {
        TowheeVector3D::Ea1Tv1(d, v);
        setAll();
    }

    /*
     * PEa1Tv1
     */
    void TowheeVector3DAtom::PEa1Tv1(double d, IAPIVector *v) {
        TowheeVector3D::PEa1Tv1(d, v);
        setAll();
    }

    /*
     * Ev1Pv2
     */
    void TowheeVector3DAtom::Ev1Pv2(IAPIVector *v1, IAPIVector *v2) {
        TowheeVector3D::Ev1Pv2(v1, v2);
        setAll();
    }

    /*
     * Ev1Mv2
     */
    void TowheeVector3DAtom::Ev1Mv2(IAPIVector *v1, IAPIVector *v2) {
        TowheeVector3D::Ev1Mv2(v1, v2);
        setAll();
    }

    /*
     * mod
     */
    void TowheeVector3DAtom::mod(IAPIVector *v) {
        TowheeVector3D::mod(v);
        setAll();
    }

    /*
     * XE
     */
   void TowheeVector3DAtom::XE(IAPIVector *v) {
        TowheeVector3D::XE(v);
        setAll();
   }

    /*
     * E
     */
   void TowheeVector3DAtom::E(double a, double b, double c) {
        TowheeVector3D::E(a, b, c);
        setAll();
   }


}
