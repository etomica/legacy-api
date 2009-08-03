/*
 *  GlotzillaBox.cpp
 *  API Glue
 *
 */

#include <glotzmd.h>
#include <typeinfo>

#include "IAPIAtom.h"
#include "IAPIBox.h"
#include "IAPISimulation.h"
#include "IAPIVector.h"
#include "IAPIMolecule.h"

#include "GlotzillaAtomList.h"
#include "GlotzillaBox.h"
#include "GlotzillaBoxEventManager.h"
#include "GlotzillaMoleculeList.h"
#include "GlotzillaMonatomicMolecule.h"
#include "GlotzillaPolymer.h"
#include "GlotzillaSpecies.h"
#include "GlotzillaSpeciesSpheresPolymer.h"
#include "GlotzillaSpeciesSpheresMono.h"

namespace glotzwrappers
{

    const int GlotzillaBox::INDEX_UNASSIGNED = -1;
    GlotzillaBox *GlotzillaBox::mInstance = NULL;

    GlotzillaBox *GlotzillaBox::instance(glotzmd::Simulation *sim) {
        if(mInstance == NULL) {
            mInstance = new GlotzillaBox(sim);
        }
        return mInstance;
    }

    GlotzillaBox::GlotzillaBox(glotzmd::Simulation* sim) : mSimulation(sim) {
        mIndex = INDEX_UNASSIGNED;
        mBoxEvtMgr = new GlotzillaBoxEventManager();
        objectManager = new ObjectManager();
        leafList = new GlotzillaAtomList();
        moleList = new GlotzillaMoleculeList();
    }

    GlotzillaBox::~GlotzillaBox() {
    }

    /*
     * setIndex()
     */
    void GlotzillaBox::setIndex(int newIndex) {
        mIndex = newIndex;
    }

    /*
     * getIndex()
     */
    int GlotzillaBox::getIndex() {
        return mIndex;
    }

    /*
     * addMolecule()
     */
    void GlotzillaBox::addMolecule(IAPIMolecule *mole) {

        if(mole->getChildList()->getAtomCount() == 0) {
printf("ERROR (Molecule has no child atoms) : Molecule NOT added to the box.\n");
        }
        else {

            GlotzillaMolecule *m = dynamic_cast<GlotzillaMolecule *>(mole);
            mSimulation->AddParticle(m->getGlotzParticle());
            objectManager->addMapping(m->getGlotzParticle()->GetSequencer(),
                                      mole);
            IAPIAtomList *as = m->getChildList();

            for(int i = 0; i < as->getAtomCount(); i++) {
                IAPIAtom *atom = as->getAtom(i);
                objectManager->addMapping(m->getGlotzParticle()->GetBead(i)->GetSequencer(), atom);
            }

            // fire atom added event
            mBoxEvtMgr->moleculeAdded(this, m);

        }
    }

    /*
     * removeMolecule()
     */
    void GlotzillaBox::removeMolecule(IAPIMolecule *mole) {

        IAPIAtomList *as = mole->getChildList();
        GlotzillaMolecule *m = dynamic_cast<GlotzillaMolecule *>(mole);

        std::vector<int> removeIdx;
        for(int i = 0; i < as->getAtomCount(); i++) {
            removeIdx.push_back(as->getAtom(i)->getLeafIndex());
        }

        std::map<IAPIAtom *, int> oldIdx;
        IAPIAtomList *origList = getLeafList();
        for(int i = 0; i < origList->getAtomCount(); i++) {
            oldIdx.insert(std::pair<IAPIAtom *, int>(origList->getAtom(i), origList->getAtom(i)->getLeafIndex()));
        }

        for(int i = 0; i < as->getAtomCount(); i++) {
            objectManager->removeMapping(m->getGlotzParticle()->GetBead(i)->GetSequencer());
        }

        // fire atom removed event (Before the memory is deallocated)
        mBoxEvtMgr->moleculeRemoved(this, m);

        objectManager->removeMapping(m->getGlotzParticle()->GetSequencer());
        mSimulation->RemoveParticle(m->getGlotzParticle());

        IAPIAtomList *leafSet = getLeafList();
        for(int i = 0; i < removeIdx.size(); i++) {
            if(removeIdx.at(i) < leafSet->getAtomCount()) {
              IAPIAtom *a = leafSet->getAtom(removeIdx.at(i));
                // fire atom leaf index changed event
                mBoxEvtMgr->atomLeafIndexChanged(this, a, oldIdx.find(a)->second);
            }
        }
    }

    /*
     * setNMolecules()
     */
    void GlotzillaBox::setNMolecules(IAPISpecies *species, int numMolecules) {

        int currentCount = getNMolecules(species);
        if(currentCount < numMolecules) {
            // Add molecules
            for(int i = 0; i < numMolecules-currentCount;  i++) {
                IAPIMolecule *mole = addNewMolecule(species);
            }
        }
        else {
            // Remove any molecules of this species type
            IAPIMoleculeList *as = getMoleculeList(species);
//            for(int i = 0; i < currentCount-numMolecules; i++) {
            for(int i = currentCount-1; i >= numMolecules; i--) {
                removeMolecule(as->getMolecule(i));
            }
        }

    }

    /*
     * getNMolecules()
     */
    int GlotzillaBox::getNMolecules(IAPISpecies *species) {

        IAPIMoleculeList *as = getMoleculeList(species);
        return as->getMoleculeCount();
    }

    /*
     * getMoleculeList()
     */
    IAPIMoleculeList *GlotzillaBox::getMoleculeList(IAPISpecies *species) {

        glotzmd::Particle *particle;

        moleList->clear();

        for(int i = 0;  i < mSimulation->GetNumberOfParticles();i++) {
            particle = mSimulation->gParticle.at(i);

            IAPIMolecule *mole = ((IAPIMolecule *)objectManager->getMapping(particle->GetSequencer()));

            if(mole->getType() == species) {
                moleList->addMolecule(mole);
            }

        }
        return moleList;

    }

    /*
     * getMoleculeList()
     */
    IAPIMoleculeList *GlotzillaBox::getMoleculeList() {

        moleList->clear();

        glotzmd::Particle *particle;

        for(int i = 0;  i < mSimulation->GetNumberOfParticles();i++) {
            particle = mSimulation->gParticle.at(i);
            IAPIMolecule *mole = ((IAPIMolecule *)objectManager->getMapping(particle->GetSequencer()));
            moleList->addMolecule(mole);
        }

        return moleList;
    }

    /*
     * getLeafList()
     */
    IAPIAtomList *GlotzillaBox::getLeafList()
    {

        leafList->clear();
        IAPIAtom *atom;

        // Currently, all Beads have a position and velocity, so return all atoms in simulation.
        for(int i = 0; i < mSimulation->GetNumberOfBeads(); i++) {
            atom = ((IAPIAtom *)objectManager->getMapping(mSimulation->gBead.at(i)->GetSequencer()));
            leafList->addAtom(atom);

        }

        return leafList;
    }

    /*
     * getBoundary()
     */
    IAPIBoundary *GlotzillaBox::getBoundary() {

        return mBoundary;
    }

    /*
     * setBoundary()
     */
    void GlotzillaBox::setBoundary(IAPIBoundary *boundary) {

        mBoundary = dynamic_cast<GlotzillaBoundary *>(boundary);
        mSimulation->SetBoundaryConditions(mBoundary->getGlotzillaBoundary());
    }

    /*
     * getEventManager()
     */
    IAPIBoxEventManager *GlotzillaBox::getEventManager() {
        return mBoxEvtMgr;
    }

    /*
     * addSpeciesNotify()
     */
    void GlotzillaBox::addSpeciesNotify(IAPISpecies *species) {
printf("WARNING : GlotzillaBox::addSpeciesNotify() NOT implemented.\n");
    }

    /*
     * removeSpeciesNotify()
     */
    void GlotzillaBox::removeSpeciesNotify(IAPISpecies *species) {
printf("WARNING : GlotzillaBox::removeSpeciesNotify() NOT implemented.\n");
    }

    /*
     * addNewMolecule()
     */
    IAPIMolecule *GlotzillaBox::addNewMolecule(IAPISpecies *species) {

        IAPIMolecule *mole = species->makeMolecule();

        addMolecule(mole);
    }

}
