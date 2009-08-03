/*
 *  GlotzillaMonatomicMolecule.h
 *  API Glue
 *
 *
 */

#ifndef GLOTZ_MONATOMICMOLECULE_WRAPPER_H
#define GLOTZ_MONATOMICMOLECULE_WRAPPER_H

#include <glotzmd.h>

#include "IAPIAtom.h"
#include "IAPIAtomList.h"
#include "IAPISpecies.h"
#include "IAPISimulation.h"

#include "GlotzillaMolecule.h"

#include "ObjectManager.h"

using namespace molesimAPI;

namespace glotzwrappers
{

    /**
      * GlotzillaMonatomicMolecule represents a physical molecule of a
      * species that has one atom.  It holds a Glotzilla native point
      * particle (glotzmd::PointParticle).
      */
    class GlotzillaMonatomicMolecule : public GlotzillaMolecule {

        public:
            /**
              * Constructor that generates a monatomic molecule with no
              * species.  This molecule creates and holds a new instance of
              * glotzmd::PointParticle.
              * @param sim Simulation that the molecule belongs to.
              */
            GlotzillaMonatomicMolecule(IAPISimulation *sim);
            /**
              * Constructor that generates a monatomic molecule of the given
              * species.  This molecule creates and holds a new instance of
              * glotzmd::PointParticle.
              * @param sim Simulation that the molecule belongs to.
              */
            GlotzillaMonatomicMolecule(IAPISimulation *sim,
                                       IAPISpecies *species);
            /**
              * Constructor that generates a monatomic molecule of the given
              * species.  This molecule holds the given instance of
              * glotzmd::PointParticle.
              * @param sim Simulation that the molecule belongs to.
              * @param particle Instance of the Glotzilla native molecule
              *        object (glotzmd::PointParticle).
              * @param species The species for this molecule.
              */
            GlotzillaMonatomicMolecule(IAPISimulation *sim,
                                       glotzmd::PointParticle *particle,
                                       IAPISpecies *species);
            ~GlotzillaMonatomicMolecule();

            // API Compliance
            virtual void addChildAtom(IAPIAtom *atom);
            virtual void removeChildAtom(IAPIAtom *atom);
            IAPIAtomList *getChildList();

            // Non-API methods
           /**
             * WARNING : This method should not be called outside of the
             *           glue layer implementation.
             * @return Returns the Glotzilla native object
             *         (glotzmd::PointParticle) that this instance is holding.
             */
            virtual glotzmd::Particle *getGlotzParticle();

        protected:
            glotzmd::PointParticle *glotzParticle;

        private:
            void init();
            void init(glotzmd::PointParticle *p);
            ObjectManager *objectManager;

    };
}
#endif
