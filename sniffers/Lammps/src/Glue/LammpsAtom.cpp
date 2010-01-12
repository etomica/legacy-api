/*
 *  LammpsAtom.cpp
 *  API Glue
 *
 */

#include "stdio.h"

#include "library.h"
#include "atom.h"

#include "LammpsAtom.h"
#include "LammpsAtomType.h"

namespace lammpssnifferwrappers
{

    LammpsAtom::LammpsAtom(LammpsSimulation *sim, IAPIAtomType *at) {

        mSim = sim;

        mAtomType = at;

        double **pos = (double **) malloc (1 * sizeof(double *));
        pos[0] = mSim->getLammpsSim()->atom->x[mLeafIndex];
        mPosition = mSim->getSpace()->makeVector(pos);

        double **vel = (double **) malloc (1 * sizeof(double *));
        vel[0] = mSim->getLammpsSim()->atom->v[mLeafIndex];
        mVel = mSim->getSpace()->makeVector(vel);

        double **force = (double **) malloc (1 * sizeof(double *));
        force[0] = mSim->getLammpsSim()->atom->f[mLeafIndex];
        mForce = mSim->getSpace()->makeVector(force);

    }

    /*
     * getIndex()
     */
    int LammpsAtom::getIndex() {
        return mIndex;
    }

    /*
     * setIndex()
     */
    void LammpsAtom::setIndex(int index) {
        mIndex = index;
    }

    /*
     * getLeafIndex()
     */
    int LammpsAtom::getLeafIndex() {
        return mLeafIndex;
    }

    /*
     * setLeafIndex()
     */
    void LammpsAtom::setLeafIndex(int newGlobalIndex) {
        mLeafIndex = newGlobalIndex;
    }

    /*
     * setParent()
     */
    void LammpsAtom::setParent(IAPIMolecule *newParent) {
        parent = newParent;
    }

    /*
     * getParentGroup()
     */
    IAPIMolecule *LammpsAtom::getParentGroup() {
        return parent;
    }

    /*
     * getType()
     */
    IAPIAtomType *LammpsAtom::getType() {
        return mAtomType;
    }

    /*
     * getPosition()
     */
    IAPIVectorMutable *LammpsAtom::getPosition() {
        return mPosition;
    }

    /*
     * getVelocity()
     */
    IAPIVectorMutable *LammpsAtom::getVelocity() {
        return mVel;
    }

    /*
     * getForce()
     */
    IAPIVectorMutable *LammpsAtom::getForce() {
        return mForce;
    }

}
