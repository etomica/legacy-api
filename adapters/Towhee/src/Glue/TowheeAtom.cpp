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

    TowheeAtom::TowheeAtom(IAPIAtomType *at, int tIndex) {
        mAtomType = at;
        mLeafIndex = -1;
        mTowheeIndex = tIndex;
        mPosition = new TowheeVector3D();
        mVelocity = new TowheeVector3D();
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

/*
        int getTriple = GLB_GET_TRIPLE;
        double values[3];
printf("  ATOM TYPE INDEX : %d\n", mAtomType->getIndex()); fflush(stdout);
printf("    TOWHEE ATOM INDEX : %d\n", mTowheeIndex); fflush(stdout);
        twh_coordstorage_(&getTriple, &mTowheeIndex, values);
        mPosition->setX(0, values[0]-15.0);
        mPosition->setX(1, values[1]-15.0);
        mPosition->setX(2, values[2]-15.0);
*/
        int get = GLB_GET;
        int tCoord = CRD_REAL;
        int one = 1;
        double values[3];
//printf("  ATOM TYPE INDEX : %d\n", mAtomType->getIndex()); fflush(stdout);
//printf("    TOWHEE ATOM INDEX : %d\n", mTowheeIndex); fflush(stdout);
        twh_coordinates_(&get, &tCoord, &mTowheeIndex, &one, &values[0], &values[1], &values[2]);
        mPosition->setX(0, values[0]-15.0);
        mPosition->setX(1, values[1]-15.0);
        mPosition->setX(2, values[2]-15.0);

//printf("      %f %f %f\n", mPosition->x(0), mPosition->x(1), mPosition->x(2)); fflush(stdout);
        return mPosition;
    }

    /*
     * getVelocity()
     */
    IAPIVectorMutable *TowheeAtom::getVelocity() {
        return mVelocity;
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
