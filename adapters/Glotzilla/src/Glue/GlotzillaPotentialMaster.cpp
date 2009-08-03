/*
 *  GlotzillaPotentialMaster.cpp
 *  API Glue
 *
 */

#include <glotzmd.h>

#include "IAPIAtom.h"
#include "IAPIMolecule.h"
#include "IAPIMoleculeList.h"
#include "GlotzillaAtom.h"
#include "GlotzillaBondHarmonic.h"
#include "GlotzillaBondFene.h"
#include "GlotzillaPolymer.h"
#include "GlotzillaPotential.h"
#include "GlotzillaPotentialMaster.h"
#include "PotentialGroup.h"

namespace glotzwrappers
{

    GlotzillaPotentialMaster::GlotzillaPotentialMaster(IAPISimulation *sim) {
        mSim = dynamic_cast<GlotzillaSimulation *>(sim);
    }

    /*
     * addPotential() - Used for inter-molecular bonding
     */
    void GlotzillaPotentialMaster::addPotential(IAPIPotentialAtomic *potential,
                                                IAPIAtomType *at1,
                                                IAPIAtomType *at2) {

        mSim->getGlotzillaSim()->AddInteraction
           (at1->getIndex(),
            at2->getIndex(),
            dynamic_cast<GlotzillaPotential *>(potential)->getGlotzPotential());
    }

    /*
     * addPotential() - Used for intra-molecular bonding
     */
    void GlotzillaPotentialMaster::addPotential(IAPIPotential *potential, IAPISpecies *species) {

        if(typeid(*potential) == typeid(PotentialGroup)) {
            PotentialGroup *pg = dynamic_cast<PotentialGroup *>(potential);
            for(int i = 0; i < pg->getPotentialCount(); i++) {
                IAPIPotential *pot = pg->getPotential(i);
                if(typeid(*pot) == typeid(GlotzillaBondHarmonic) ||
                   typeid(*pot) == typeid(GlotzillaBondFene)) {

                    IAPIMoleculeList *moleList = mSim->getBox(0)->getMoleculeList(species);

                    for(int j = 0; j < pg->getPairCount(i); j++) {
                        int atomIdx1 = pg->getAtomIndex1(i, j);
                        int atomIdx2 = pg->getAtomIndex2(i, j);

                        for(int k = 0; k < moleList->getMoleculeCount(); k++) {
                            IAPIMolecule *mole = moleList->getMolecule(k);
                            if(typeid(*mole) == typeid(GlotzillaPolymer)) {
                                IAPIAtomList *atomList = mole->getChildList();
                                IAPIAtom *atom1 = atomList->getAtom(atomIdx1);
                                IAPIAtom *atom2 = atomList->getAtom(atomIdx2);
                                glotzmd::Bead *bead1 = dynamic_cast<GlotzillaAtom *>(atom1)->getGlotzBead();
                                glotzmd::Bead *bead2 = dynamic_cast<GlotzillaAtom *>(atom2)->getGlotzBead();
                                glotzmd::Spring *spring;
                                if(typeid(*pot) == typeid(GlotzillaBondHarmonic)) {
                                    GlotzillaBondHarmonic *bond = dynamic_cast<GlotzillaBondHarmonic *>(pot);
                                    spring = new glotzmd::HarmonicSpring();
                                    spring->SetSpringConstant(bond->getSpringConstant());
                                    spring->SetTargetExtent(bond->getTargetExtent());
                                }
                                else if(typeid(*pot) == typeid(GlotzillaBondFene)) {
                                    GlotzillaBondFene *bond = dynamic_cast<GlotzillaBondFene *>(pot);
                                    spring = new glotzmd::FeneSpring();
                                    spring->SetSpringConstant(bond->getSpringConstant());
                                    dynamic_cast<glotzmd::FeneSpring *>(spring)->SetTargetExtent(bond->getTargetExtent());
                                }

                                // Set the bonds atoms
                                spring->Connect(bead1, bead2);

                                // call AddBond() on the polymer
                                dynamic_cast<glotzmd::Polymer *>
                                     (dynamic_cast<GlotzillaMolecule *>(mole)->
                                     getGlotzParticle())->AddBond(spring, bead1, bead2);

                                // If the polymer has already been added to the glotzilla simulation, then
                                // then this bond needs to be directly added to the glotzilla simulation
                                // spring list (gSpring).
                                mSim->getGlotzillaSim()->gSpring.Insert(spring);
                            }

                        }
                    }
                }
                else {
                    printf("WARNING : Unknown bond type within PotentialGroup.\n");
                    fflush(stdout);
                }
            }
        }
        else {
            printf("ERROR : GlotzillaPotentialMaster::addPotential() => potential is not a PotentialGroup\n");
            fflush(stdout);
        }
    }

}
