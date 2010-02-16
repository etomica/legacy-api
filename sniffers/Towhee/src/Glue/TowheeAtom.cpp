/*
 *  TowheeAtom.cpp
 *  API Glue
 *
 *
 */

#include "stdio.h"

#include "preproc.h"

#include "TowheeAtom.h"

extern "C" { void twh_coordstorage_(int *, int *, double *); }
extern "C" { void twh_coordinates_(int *, int *, int *, int *, double *, double *, double *); }

namespace towheesnifferwrappers
{

    TowheeAtom::TowheeAtom(IAPIAtomType *at, int tIndex, IAPIMolecule *p) {
        mAtomType = at;
        mLeafIndex = -1;
        mParent = p;
        int tCoord = CRD_REAL;
        int one = 1;
        mPosition = new TowheeVector3DAtom(this, &twh_coordinates_, tCoord, one);
    }

    /*
     * getIndex()
     */
    int TowheeAtom::getIndex() {
        return mIndex;
    }

    /*
     * setIndex()
     */
    void TowheeAtom::setIndex(int index) {
        mIndex = index;
    }

    /*
     * getLeafIndex()
     */
    int TowheeAtom::getLeafIndex() {
        return mLeafIndex;
    }

    /*
     * setLeafIndex()
     */
    void TowheeAtom::setLeafIndex(int newLeafIndex) {
        mLeafIndex = newLeafIndex;
    }

    /*
     * getPosition()
     */
    IAPIVectorMutable *TowheeAtom::getPosition() {

        mPosition->update();

        return mPosition;
    }

    /*
     * getVelocity()
     */
    IAPIVectorMutable *TowheeAtom::getVelocity() {
        printf("TowheeAtom::getVelocity() is not implemented.\n");
    }

    /*
     * setParent()
     */
    void TowheeAtom::setParent(IAPIMolecule *newParent) {
        printf("ERROR : TowheeAtom::setParent(IAPIMolecule *) is not implemeted.\n");
    }

    /*
     * getParentGroup()
     */
    IAPIMolecule *TowheeAtom::getParentGroup() {
        return mParent;
    }

    /*
     * getType()
     */
    IAPIAtomType *TowheeAtom::getType() {
        return mAtomType;
    }


}
