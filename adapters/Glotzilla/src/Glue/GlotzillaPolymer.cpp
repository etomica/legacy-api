/*
 *  GlotzillaPolymer.cpp
 *  API Glue
 *
 */

#include <glotzmd.h>

#include "GlotzillaAtomList.h"
#include "GlotzillaAtomType.h"
#include "GlotzillaPolymer.h"
#include "GlotzillaAtom.h"

namespace glotzwrappers
{

    GlotzillaPolymer::GlotzillaPolymer(IAPISimulation *sim) : GlotzillaMolecule(sim, (IAPISpecies *)NULL) {
        init();
    }

    GlotzillaPolymer::GlotzillaPolymer(IAPISimulation *sim, IAPISpecies *species) : GlotzillaMolecule(sim, species) {
        init();
    }

    GlotzillaPolymer::GlotzillaPolymer(IAPISimulation *sim, glotzmd::Polymer *poly, IAPISpecies *species) :
                                               GlotzillaMolecule(sim, species) {
        init(poly);
    }

    GlotzillaPolymer::~GlotzillaPolymer() {
    }

    /*
     * init
     */
    void GlotzillaPolymer::init() {
        init(new glotzmd::Polymer);

    }

    /*
     * init
     */
    void GlotzillaPolymer::init(glotzmd::Polymer *p) {
        glotzPolymer = p;
        objectManager = new ObjectManager();
    }

    /*
     * addChildAtom()
     */
    void GlotzillaPolymer::addChildAtom(IAPIAtom *atom) {

        
        if(typeid(*atom)  == typeid(GlotzillaAtom)) {
            atom->setParent(this);
            GlotzillaAtom *a = dynamic_cast<GlotzillaAtom *>(atom);
            glotzPolymer->AddBead(a->getGlotzBead());

            objectManager->addMapping(glotzPolymer->GetBeadPtr(
                         a->getGlotzBead()->GetSequencer())->GetSequencer(),
                         atom);
        }
        else {
            printf("WARNING : GlotzillaPolymer.addChildAtom() -> Unknown atom type.\n");
        }
    }

    /*
     * removeChildAtom()
     */
    void GlotzillaPolymer::removeChildAtom(IAPIAtom *atom) {
printf("WARNING : GlotzillaPolymer::removeChildAtom() is NOT implemented yet.  Polymer does not have a method to remove a Bead.  Could remove Bead from simulation, although there would be a disconnect between the Simulation and Polymer then?  Probably going to need to remove atom from Polymer and simulation manually.\n");

        int numBeads = glotzPolymer->GetNumberOfBeads();
printf(" **  numBeads(Polymer) : %d\n", numBeads);

        GlotzillaAtom *a = dynamic_cast<GlotzillaAtom *>(atom);
        a->getGlotzBead();
        for(int i = 0; i < numBeads; i++) {
            if(glotzPolymer->GetBead(i) == a->getGlotzBead()) {
printf("  found bead to remove but did NOT remove!!!\n");
printf("  also need to remove from mapping (if mapping not valid for other atoms.\n");
            }
        }

    }

    /*
     * getChildList()
     */
    IAPIAtomList *GlotzillaPolymer::getChildList() {

        mAtomList->clear();
        int numBeads = glotzPolymer->GetNumberOfBeads();

        for(int i = 0; i < numBeads; i++) {
            IAPIAtom *at = (IAPIAtom *)objectManager->getMapping(glotzPolymer->GetBead(i)->GetSequencer());

            mAtomList->addAtom(at);

        }
        return mAtomList;

    }

    /*
     * setVelocity()
     */
    void GlotzillaPolymer::setVelocity(GlotzillaVector *velocity) {
        glotzPolymer->SetVelocity(*velocity->getGlotzVector());
    }

    /*
     * modifyVelocity()
     */
    void GlotzillaPolymer::modifyVelocity(GlotzillaVector *velocity) {
        glotzPolymer->ModifyVelocity(*velocity->getGlotzVector());
    }

    /*
     * rescaleVelocity()
     */
    void GlotzillaPolymer::rescaleVelocity(double velocity) {
        glotzPolymer->RescaleVelocity(velocity);
    }

    /*
     * invertVelocity()
     */
    void GlotzillaPolymer::invertVelocity() {
        glotzPolymer->InvertVelocity();
    }

    /*
     * setPosition()
     */
    void GlotzillaPolymer::setPosition(GlotzillaVector *velocity) {
        glotzPolymer->SetPosition(*velocity->getGlotzVector());
    }

    /*
     * setPositionInBox()
     */
    void GlotzillaPolymer::setPositionInBox(GlotzillaVector *velocity) {
        glotzPolymer->SetPositionInBox(*velocity->getGlotzVector());
    }

    /*
     * getGlotzParticle()
     */
    glotzmd::Particle *GlotzillaPolymer::getGlotzParticle() {
        return glotzPolymer;
    }

}
