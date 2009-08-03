/*
 *  GlotzillaMonatomicMolecule.cpp
 *  API Glue
 *
 */

#include <glotzmd.h>

#include "GlotzillaAtomList.h"
#include "GlotzillaMonatomicMolecule.h"
#include "GlotzillaAtom.h"
#include "GlotzillaAtomType.h"

namespace glotzwrappers
{

    GlotzillaMonatomicMolecule::GlotzillaMonatomicMolecule(IAPISimulation *sim) : GlotzillaMolecule(sim, (IAPISpecies *)NULL) {
        init();
    }

    GlotzillaMonatomicMolecule::GlotzillaMonatomicMolecule(IAPISimulation *sim, IAPISpecies *species) : GlotzillaMolecule(sim, species) {
        init();
    }

    GlotzillaMonatomicMolecule::GlotzillaMonatomicMolecule(IAPISimulation *sim, glotzmd::PointParticle *particle, IAPISpecies *species) :
                                   GlotzillaMolecule(sim, species) {
        init(particle);
    }

    /*
     * init()
     */
    void GlotzillaMonatomicMolecule::init() {
        init(new glotzmd::PointParticle());
    }

    /*
     * init()
     */
    void GlotzillaMonatomicMolecule::init(glotzmd::PointParticle *p) {
        glotzParticle = p;
        objectManager = new ObjectManager();
        IAPIAtom *atom = new GlotzillaAtom
             (mSim, new GlotzillaAtomType(p->xBead->xType));
        objectManager->addMapping(glotzParticle->xBead->GetSequencer(),
                                  atom);
    }

    GlotzillaMonatomicMolecule::~GlotzillaMonatomicMolecule() {
    }

    /*
     * addChildAtom()
     */
    void GlotzillaMonatomicMolecule::addChildAtom(IAPIAtom *atom) {

        atom->setParent(this);

        // Not using a while loop in so as to avoid an
        // unterminated loop in case of an error in AtomList.
        // atomCount should NEVER be greater than 1 here.
        int atomCount = glotzParticle->GetNumberOfBeads();

        for(int i = 0; i < atomCount; i++) {
          objectManager->removeMapping(glotzParticle->xBead->GetSequencer());
          delete glotzParticle->xBead;
        }
        GlotzillaAtom *a = dynamic_cast<GlotzillaAtom *>(atom);
        glotzParticle->xBead = a->getGlotzBead();
        objectManager->addMapping(glotzParticle->xBead->GetSequencer(), dynamic_cast<IAPIAtom *>(atom));
        IAPIVector *v = a->getPosition();
        glotzmath::glotz_vec position(v->getX(0), v->getX(1), v->getX(2));
        glotzParticle->SetPosition(position);
    }

    /*
     * removeChildAtom()
     */
    void GlotzillaMonatomicMolecule::removeChildAtom(IAPIAtom *atom) {
        if(dynamic_cast<GlotzillaAtom *>(atom)->getGlotzBead()->GetSequencer() ==
                                            glotzParticle->xBead->GetSequencer()) {
            delete glotzParticle->xBead;
            glotzParticle->xBead = NULL;
            objectManager->removeMapping(glotzParticle->xBead->GetSequencer());
        }
    }

    /*
     * getChildList()
     */
    IAPIAtomList *GlotzillaMonatomicMolecule::getChildList() {
        mAtomList->clear();
        if(glotzParticle->xBead != NULL) {
            IAPIAtom *a = (IAPIAtom *)objectManager->getMapping(glotzParticle->xBead->GetSequencer());
            mAtomList->addAtom(a);
        }
        return mAtomList;

    }

    /*
     * getGlotzParticle()
     */
    glotzmd::Particle * GlotzillaMonatomicMolecule::getGlotzParticle() {
        return glotzParticle;
    }

}
