/*
 *  TowheeAtom.cpp
 *  API Glue
 *
 *
 */

#include "stdio.h"

#include "preproc.h"

#include "TowheeAtom.h"
#include "TowheeVector3D.h"

extern "C" { void twh_coordstorage_(int *, int *, double *); }
extern "C" { void twh_coordinates_(int *, int *, int *, int *, double *, double *, double *); }

namespace towheewrappers
{

    TowheeAtom::TowheeAtom(IAPIAtomType *at, int tIndex, IAPIBoundary *boundary) {
        mAtomType = at;
        mLeafIndex = -1;
        mTowheeIndex = tIndex;
        int get = GLB_GET;
        int tCoord = CRD_REAL;
        int one = 1;
        IAPIVectorMutable *offsetVector = new TowheeVector3D(boundary->getCenter()->getX(0),
                                                             boundary->getCenter()->getX(1),
                                                             boundary->getCenter()->getX(2));
        mPosition = new TowheeVector3DAtom(&twh_coordinates_, tCoord, mTowheeIndex, one,
                                               offsetVector);
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
        return NULL;
    }

    /*
     * setParent()
     */
    void TowheeAtom::setParent(IAPIMolecule *newParent) {
        mParent = newParent;
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
