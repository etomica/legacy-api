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

namespace lammpswrappers
{

    LammpsAtom::LammpsAtom(IAPISimulation *sim) {
        init(sim, 0.0, 0.0, 0.0, new LammpsAtomType());
    }

    LammpsAtom::LammpsAtom(IAPISimulation *sim, IAPIAtomType *at) {
        init(sim, 0.0, 0.0, 0.0, at);
    }

    LammpsAtom::LammpsAtom(IAPISimulation *sim, double x,
                                   double y, double z) {
        init(sim, x, y, z, new LammpsAtomType());
    }

    LammpsAtom::LammpsAtom(IAPISimulation *sim, double x, double y,
                                   double z, IAPIAtomType *at) {
        init(sim, x, y, z, at);
    }

    LammpsAtom::LammpsAtom(IAPISimulation *sim, IAPIVector *pos) {
        init(sim, pos->getX(0), pos->getX(1), pos->getX(2), new LammpsAtomType());
    }

    LammpsAtom::LammpsAtom(IAPISimulation *sim, IAPIVector *pos,
                                   IAPIAtomType *at) {
        init(sim, pos->getX(0), pos->getX(1), pos->getX(2), at);
    }

    LammpsAtom::LammpsAtom(IAPISimulation *sim, IAPIAtomType *at, int leafIndex) {

        mSim = dynamic_cast<LammpsSimulation *>(sim);

printf("WARNING : LammpsAtom::init() -> hardcoded bond_per_atom is NOT ok.\n");
mSim->getLammpsSim()->atom->bond_per_atom = 1;

        setLeafIndex(leafIndex);
        mAtomType = at;

        mPosition = mSim->getSpace()->makeVector(mSim->getLammpsSim()->atom->x[mLeafIndex]);
        mVel = mSim->getSpace()->makeVector(mSim->getLammpsSim()->atom->v[mLeafIndex]);
        mForce = mSim->getSpace()->makeVector(mSim->getLammpsSim()->atom->f[mLeafIndex]);

        char command[512];

        sprintf(command,
                "mass %d %f",
                mAtomType->getIndex(),
                mAtomType->getMass());
printf("lammps_command : %s\n", command); fflush(stdout);
        lammps_command(mSim->getLammpsSim(), command);
    }

    /*
     * init()
     */
    void LammpsAtom::init(IAPISimulation *sim, double x, double y, double z, IAPIAtomType *at) {
        mSim = dynamic_cast<LammpsSimulation *>(sim);

printf("WARNING : LammpsAtom::init() -> hardcoded bond_per_atom is NOT ok.\n");
mSim->getLammpsSim()->atom->bond_per_atom = 1;

        mAtomType = at;

        char command[512];
        sprintf(command,
                "create_atoms %d single %f %f %f units box",
                mAtomType->getIndex(),
                x, y, z);
printf("lammps_command : %s\n", command); fflush(stdout);
        lammps_command(mSim->getLammpsSim(), command);

        int natoms = (int)mSim->getLammpsSim()->atom->natoms;
        // lammps tags start at 1, leaf index start at 0
        setLeafIndex(mSim->getLammpsSim()->atom->tag[natoms-1]-1);

        mPosition = mSim->getSpace()->makeVector(mSim->getLammpsSim()->atom->x[mLeafIndex]);
        mVel = mSim->getSpace()->makeVector(mSim->getLammpsSim()->atom->v[mLeafIndex]);
        mForce = mSim->getSpace()->makeVector(mSim->getLammpsSim()->atom->f[mLeafIndex]);

        sprintf(command,
                "mass %d %f",
                mAtomType->getIndex(),
                mAtomType->getMass());
printf("lammps_command : %s\n", command); fflush(stdout);
        lammps_command(mSim->getLammpsSim(), command);
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
        if(mSim->getState() == LammpsSimulation::UNINITIALIZED) {
            parent = newParent;
        }
        else {
            printf("ERROR : LammpsAtom::setParent CANNOT set parent after simulation is initialized.\n");
        }
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
