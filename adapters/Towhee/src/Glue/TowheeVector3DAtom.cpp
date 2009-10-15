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

namespace towheewrappers
{

    TowheeVector3DAtom::TowheeVector3DAtom(TowheeAtom *atom,
                                           void (*fnct)(int *, int *, int *, int *, double *, double *, double *),
                                           int ia1, int ia2, int ia3/*, IAPIVector *offsetVector*/) {
        mFunction = fnct;
        iArg1 = ia1;
        iArg2 = ia2;
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
//printf("TowheeVector3DAtom::getX : %f  ", vecPos[index]);
//printf("  offset : %f  %f  %f\n", offset->getX(0), offset->getX(1), offset->getX(2)); fflush(stdout);
        update();
        IAPIVector *offset = getOffset();
        return vecPos[index]-offset->getX(index);
    }

    /*
     * setX
     */
    void TowheeVector3DAtom::setX(int index, double value) {
printf("TowheeVector3DAtom::setX\n"); fflush(stdout);
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
        (*mFunction)(&set, &iArg1, &iArg2, &iArg3, &vecPos[0], &vecPos[1], &vecPos[2]);

        // Need to change the center of mas of the molecule
        // which this atom is a part of.
        int tCoord = CRD_REAL;
        int ctrInitial = CTR_INITIAL;
        int failFlag;
        int moleIndex = mAtom->getParentGroup()->getIndex()+1;
        int ibox = dynamic_cast<TowheeMolecule *>(mAtom->getParentGroup())->getBox()->getIndex()+1;
        twh_ctrmas_(&failFlag, &tCoord, &ibox, &moleIndex, &ctrInitial);

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
printf("TowheeVector3DAtom::E(v)\n"); fflush(stdout);
        update();
        TowheeVector3D::E(v);
        setAll();
    }

    /*
     * E
     */
    void TowheeVector3DAtom::E(double d) {
printf("TowheeVector3DAtom::E(d)\n"); fflush(stdout);
        update();
        TowheeVector3D::E(d);
        setAll();
    }

    /*
     * E
     */
    void TowheeVector3DAtom::E(double d[]) {
printf("TowheeVector3DAtom::E(d[])\n"); fflush(stdout);
        update();
        TowheeVector3D::E(d);
        setAll();
    }

    /*
     * PE
     */
    void TowheeVector3DAtom::PE(IAPIVector *v) {
printf("TowheeVector3DAtom::PE(v) : %f  %f  %f\n", v->getX(0), v->getX(1), v->getX(2)); fflush(stdout);
        update();
        TowheeVector3D::PE(v);
        setAll();
    }

    /*
     * PE
     */
    void TowheeVector3DAtom::PE(double d) {
printf("TowheeVector3DAtom::PE(d)\n"); fflush(stdout);
        update();
        TowheeVector3D::PE(d);
        setAll();
    }

    /*
     * ME
     */
    void TowheeVector3DAtom::ME(IAPIVector *v) {
printf("TowheeVector3DAtom::ME(v)\n"); fflush(stdout);
        update();
        TowheeVector3D::ME(v);
        setAll();
    }

    /*
     * TE
     */
    void TowheeVector3DAtom::TE(IAPIVector *v) {
printf("TowheeVector3DAtom::TE(v)\n"); fflush(stdout);
        update();
        TowheeVector3D::TE(v);
        setAll();
    }

    /*
     * TE
     */
    void TowheeVector3DAtom::TE(double d) {
printf("TowheeVector3DAtom::TE(d)\n"); fflush(stdout);
        update();
        TowheeVector3D::TE(d);
        setAll();
    }

    /*
     * DE
     */
    void TowheeVector3DAtom::DE(IAPIVector *v) {
printf("TowheeVector3DAtom::DE(v)\n"); fflush(stdout);
        update();
        TowheeVector3D::DE(v);
        setAll();
    }

    /*
     * Ea1Tv1
     */
    void TowheeVector3DAtom::Ea1Tv1(double d, IAPIVector *v) {
printf("TowheeVector3DAtom::Ea1Tv1(d, v)\n"); fflush(stdout);
        update();
        TowheeVector3D::Ea1Tv1(d, v);
        setAll();
    }

    /*
     * PEa1Tv1
     */
    void TowheeVector3DAtom::PEa1Tv1(double d, IAPIVector *v) {
printf("TowheeVector3DAtom::PEa1Tv1(d, v)\n"); fflush(stdout);
        update();
        TowheeVector3D::PEa1Tv1(d, v);
        setAll();
    }

    /*
     * Ev1Pv2
     */
    void TowheeVector3DAtom::Ev1Pv2(IAPIVector *v1, IAPIVector *v2) {
printf("TowheeVector3DAtom::Ev1Pv2(d, v)\n"); fflush(stdout);
        update();
        TowheeVector3D::Ev1Pv2(v1, v2);
        setAll();
    }

    /*
     * Ev1Mv2
     */
    void TowheeVector3DAtom::Ev1Mv2(IAPIVector *v1, IAPIVector *v2) {
printf("TowheeVector3DAtom::Ev1Mv2(d, v)\n"); fflush(stdout);
        update();
        TowheeVector3D::Ev1Mv2(v1, v2);
        setAll();
    }

    /*
     * mod
     */
    void TowheeVector3DAtom::mod(IAPIVector *v) {
printf("TowheeVector3DAtom::mod()\n"); fflush(stdout);
        update();
        TowheeVector3D::mod(v);
        setAll();
    }

    /*
     * XE
     */
   void TowheeVector3DAtom::XE(IAPIVector *v) {
printf("TowheeVector3DAtom::XE()\n"); fflush(stdout);
        update();
        TowheeVector3D::XE(v);
        setAll();
   }

    /*
     * E
     */
   void TowheeVector3DAtom::E(double a, double b, double c) {
printf("TowheeVector3DAtom::E(a, b, c)\n"); fflush(stdout);
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
