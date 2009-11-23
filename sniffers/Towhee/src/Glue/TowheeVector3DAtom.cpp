/*
 *  TowheeVector3DAtom.cpp
 *  API Glue
 *
 */

#include "stdio.h"

#include "preproc.h"

#include "TowheeVector3DAtom.h"
#include "TowheeAtom.h"
#include "TowheeMolecule.h"

extern "C" { void twh_ctrmas_(int *, int *, int *, int *, int *); }

namespace towheesnifferwrappers
{

    TowheeVector3DAtom::TowheeVector3DAtom(TowheeAtom *atom,
                                           void (*fnct)(int *, int *, int *, int *, double *, double *, double *),
                                           int ia1, int ia3/*, IAPIVector *offsetVector*/) {
        mFunction = fnct;
        iArg1 = ia1;
        iArg3 = ia3;
//        offset = offsetVector;
        mAtom = atom;
    }

    /*
     * assignTo
     */
    void TowheeVector3DAtom::assignTo(double values[]) {
        update();
        TowheeVector3D::assignTo(values);
        IAPIVector *offset = getOffset();
        values[0] -= offset->getX(0);
        values[1] -= offset->getX(1);
        values[2] -= offset->getX(2);
    }

    /*
     * getX
     */
    double TowheeVector3DAtom::getX(int index) {
        update();
        IAPIVector *offset = getOffset();
        return vecPos[index]-offset->getX(index);
    }

    /*
     * setX
     */
    void TowheeVector3DAtom::setX(int index, double value) {
        TowheeVector3D::setX(index, value);
        IAPIVector *offset = getOffset();
        vecPos[index] += offset->getX(index);
        setAll();
    }

    /*
     * setAll
     */
    void TowheeVector3DAtom::setAll() {
        int set = GLB_SET;
        int moleIndex = mAtom->getParentGroup()->getIndex()+1;
        int atomIndex = mAtom->getIndex()+1;
printf("args : %d  %d  %d\n", iArg1, moleIndex, atomIndex); fflush(stdout);

        (*mFunction)(&set, &iArg1, &moleIndex, &atomIndex, &vecPos[0], &vecPos[1], &vecPos[2]);

        // Need to change the center of mass of the molecule
        // which this atom is a part of.
        int tCoord = CRD_REAL;
        int ctrInitial = CTR_INITIAL;
        int failFlag;
        int ibox = dynamic_cast<TowheeMolecule *>(mAtom->getParentGroup())->getBox()->getIndex()+1;
printf("ibox : %d  moleIndex : %d\n", ibox, moleIndex); fflush(stdout);
        twh_ctrmas_(&failFlag, &tCoord, &ibox, &moleIndex, &ctrInitial);

    }

    /*
     * update
     */
    void TowheeVector3DAtom::update() {
        int get = GLB_GET;
        int moleIndex = mAtom->getParentGroup()->getIndex()+1;
        int atomIndex = mAtom->getIndex()+1;
//printf("UPDATE:: %d  %d  %d\n", iArg1, moleIndex, atomIndex); fflush(stdout);
//printf("UPDATE:: %d  %d  %d\n", iArg1, iArg2, iArg3); fflush(stdout);
        (*mFunction)(&get, &iArg1, &moleIndex, &atomIndex, &vecPos[0], &vecPos[1], &vecPos[2]);
//        (*mFunction)(&get, &iArg1, &iArg2, &iArg3, &vecPos[0], &vecPos[1], &vecPos[2]);
//printf("  POSITION : %f  %f  %f\n", vecPos[0], vecPos[1], vecPos[2]); fflush(stdout);
    }

    /*
     * E
     */
    void TowheeVector3DAtom::E(IAPIVector *v) {
        update();
        TowheeVector3D::E(v);
        setAll();
    }

    /*
     * E
     */
    void TowheeVector3DAtom::E(double d) {
        update();
        TowheeVector3D::E(d);
        setAll();
    }

    /*
     * E
     */
    void TowheeVector3DAtom::E(double d[]) {
        update();
        TowheeVector3D::E(d);
        setAll();
    }

    /*
     * PE
     */
    void TowheeVector3DAtom::PE(IAPIVector *v) {
        update();
        TowheeVector3D::PE(v);
        setAll();
    }

    /*
     * PE
     */
    void TowheeVector3DAtom::PE(double d) {
        update();
        TowheeVector3D::PE(d);
        setAll();
    }

    /*
     * ME
     */
    void TowheeVector3DAtom::ME(IAPIVector *v) {
        update();
        TowheeVector3D::ME(v);
        setAll();
    }

    /*
     * TE
     */
    void TowheeVector3DAtom::TE(IAPIVector *v) {
        update();
        TowheeVector3D::TE(v);
        setAll();
    }

    /*
     * TE
     */
    void TowheeVector3DAtom::TE(double d) {
        update();
        TowheeVector3D::TE(d);
        setAll();
    }

    /*
     * DE
     */
    void TowheeVector3DAtom::DE(IAPIVector *v) {
        update();
        TowheeVector3D::DE(v);
        setAll();
    }

    /*
     * Ea1Tv1
     */
    void TowheeVector3DAtom::Ea1Tv1(double d, IAPIVector *v) {
        update();
        TowheeVector3D::Ea1Tv1(d, v);
        setAll();
    }

    /*
     * PEa1Tv1
     */
    void TowheeVector3DAtom::PEa1Tv1(double d, IAPIVector *v) {
        update();
        TowheeVector3D::PEa1Tv1(d, v);
        setAll();
    }

    /*
     * Ev1Pv2
     */
    void TowheeVector3DAtom::Ev1Pv2(IAPIVector *v1, IAPIVector *v2) {
        update();
        TowheeVector3D::Ev1Pv2(v1, v2);
        setAll();
    }

    /*
     * Ev1Mv2
     */
    void TowheeVector3DAtom::Ev1Mv2(IAPIVector *v1, IAPIVector *v2) {
        update();
        TowheeVector3D::Ev1Mv2(v1, v2);
        setAll();
    }

    /*
     * mod
     */
    void TowheeVector3DAtom::mod(IAPIVector *v) {
        update();
        TowheeVector3D::mod(v);
        setAll();
    }

    /*
     * XE
     */
   void TowheeVector3DAtom::XE(IAPIVector *v) {
        update();
        TowheeVector3D::XE(v);
        setAll();
   }

    /*
     * E
     */
   void TowheeVector3DAtom::E(double a, double b, double c) {
        update();
        TowheeVector3D::E(a, b, c);
        setAll();
   }

    /*
     * getOffset()
     */
    IAPIVector *TowheeVector3DAtom::getOffset() {

        IAPIBoundary *boundary = dynamic_cast<TowheeMolecule *>
                     (mAtom->getParentGroup())->getBox()->getBoundary();
        IAPIVector *offsetVector = boundary->getCenter();

        return offsetVector;
    }


}
