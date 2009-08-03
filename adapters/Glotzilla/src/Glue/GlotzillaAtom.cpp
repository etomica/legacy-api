/*
 *  GlotzillaAtom.cpp
 *  API Glue
 *
 *
 */

#include "stdio.h"

#include <glotzmd.h>

#include "GlotzillaAtom.h"
#include "GlotzillaAtomType.h"
#include "GlotzillaMolecule.h"

namespace glotzwrappers
{

    GlotzillaAtom::GlotzillaAtom(IAPISimulation *sim)  {
        init(sim, 0.0, 0.0, 0.0, new GlotzillaAtomType());
    }

    GlotzillaAtom::GlotzillaAtom(IAPISimulation *sim, IAPIAtomType *at) {
        init(sim, 0.0, 0.0, 0.0, at);
    }

    GlotzillaAtom::GlotzillaAtom(IAPISimulation *sim, double x, double y, double z) {
        init(sim, x, y, z, new GlotzillaAtomType());
    }

    GlotzillaAtom::GlotzillaAtom(IAPISimulation *sim, double x, double y, double z, IAPIAtomType *at) {
        init(sim, x, y, z, at);
    }

    GlotzillaAtom::GlotzillaAtom(IAPISimulation *sim, IAPIVector *v) {
        init(sim, v->getX(0), v->getX(1), v->getX(2), new GlotzillaAtomType());
    }

    GlotzillaAtom::GlotzillaAtom(IAPISimulation *sim, IAPIVector *v, IAPIAtomType *at) {
        init(sim, v->getX(0), v->getX(1), v->getX(2), at);
    }

    GlotzillaAtom::GlotzillaAtom(IAPISimulation *sim, glotzmd::Bead *bead) {
        mSim = dynamic_cast<GlotzillaSimulation *>(sim);
        glotzBead = bead;
        mAtomType = new GlotzillaAtomType(glotzBead->GetType());
        mPosition = mSim->getSpace()->makeVector(&(glotzBead->GetPosition()));
    }

    GlotzillaAtom::~GlotzillaAtom() {
    }

    void GlotzillaAtom::init(IAPISimulation *sim, double x, double y, double z, IAPIAtomType *at) {
        mSim = dynamic_cast<GlotzillaSimulation *>(sim);
        glotzBead = new glotzmd::Bead(x, y, z);
        mPosition = mSim->getSpace()->makeVector(&(glotzBead->GetPosition()));
        mVelocity = mSim->getSpace()->makeVector(&(glotzBead->GetVelocity()));
        mAtomType = at;
        glotzBead->SetType(mAtomType->getIndex());
        glotzBead->SetMass(mAtomType->getMass());
        parent = NULL;
    }

    /*
     * getIndex()
     */
    int GlotzillaAtom::getIndex() {

        if(parent == NULL) {
            return -1;
        }
        else {
            GlotzillaMolecule *mole = dynamic_cast<GlotzillaMolecule *>(parent);
            for(int i = 0; i < mole->getGlotzParticle()->GetNumberOfBeads(); i++) {
                if(mole->getGlotzParticle()->GetBead(i) == glotzBead) {
                    return i;
                }
            }
        }
    }

    /*
     * setIndex()
     */
    void GlotzillaAtom::setIndex(int index) {
    }

    /*
     * getLeafIndex()
     */
    int GlotzillaAtom::getLeafIndex() {
        return mSim->getGlotzillaSim()->gBead.GetIndexOf(glotzBead);
    }

    /*
     * setLeafIndex()
     */
    void GlotzillaAtom::setLeafIndex(int newLeafIndex) {
    }

    /*
     * getPosition()
     */
    IAPIVectorMutable *GlotzillaAtom::getPosition() {
        return mPosition;
    }

    /*
     * getVelocity()
     */
    IAPIVectorMutable *GlotzillaAtom::getVelocity() {
      return mVelocity;
    }

    /*
     * setParent()
     */
    void GlotzillaAtom::setParent(IAPIMolecule *newParent) {
        parent = newParent;
    }

    /*
     * getParentGroup()
     */
    IAPIMolecule *GlotzillaAtom::getParentGroup() {
        return parent;
    }

    /*
     * getType()
     */
    IAPIAtomType *GlotzillaAtom::getType() {
        return dynamic_cast<IAPIAtomType *>(mAtomType);
    }

    /*
     * getGlotzBead()
     */
    glotzmd::Bead *GlotzillaAtom::getGlotzBead() {
        return glotzBead;
    }

}
