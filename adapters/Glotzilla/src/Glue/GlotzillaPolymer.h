/*
 *  GlotzillaPolymer.h
 *  API Glue
 *
 */

#ifndef GLOTZ_POLYMERMOLECULE_WRAPPER_H
#define GLOTZ_POLYMERMOLECULE_WRAPPER_H

#include <glotzmd.h>

#include "IAPIAtom.h"
#include "IAPIAtomPositioned.h"
#include "IAPIAtomList.h"
#include "IAPIAtomType.h"
#include "IAPISimulation.h"
#include "GlotzillaMolecule.h"
#include "GlotzillaVector.h"

#include "ObjectManager.h"

using namespace molesimAPI;

namespace glotzwrappers
{

    /**
      * GlotzillaPolymer represents a physical polymer of a species
      * that has one or more atoms.  It holds a Glotzilla native polymer
      * (glotzmd::Polymer).
      */
    class GlotzillaPolymer : public GlotzillaMolecule {

        public:
            /**
              * Constructor that generates a polymer with no species.
              * This polymer creates and holds a new instance of
              * glotzmd::Polymer.
              * @param sim Simulation that the molecule belongs to.
              */
            GlotzillaPolymer(IAPISimulation *sim);
            /**
              * Constructor that generates a polymer of the given species.
              * This polymer creates and holds a new instance of
              * glotzmd::Polymer.
              * @param sim Simulation that the molecule belongs to.
              * @param species The species for this molecule.
              */
            GlotzillaPolymer(IAPISimulation *sim, IAPISpecies *species);
            /**
              * Constructor that generates a polymer of the given species.
              * This polymer holds the given instance of * glotzmd::Polymer.
              * @param sim Simulation that the molecule belongs to.
              * @param poly Instance of a Glotzilla native polymer object
              *             (glotzmd::Polymer).
              * @param species The species for this molecule.
              */
            GlotzillaPolymer(IAPISimulation *sim, glotzmd::Polymer *poly, IAPISpecies *species);
            ~GlotzillaPolymer();

            // API Compliance
            virtual void addChildAtom(IAPIAtom *atom);
            /**
              * Removes the given atom as a child of this Molecule.
              * @param atom Atom to remove from molecule
              * @todo This method is not implemented CORRECTLY.  Do not use
              *       the method.
              */
            virtual void removeChildAtom(IAPIAtom *atom);
            virtual IAPIAtomList *getChildList();

            // Non-API methods
            /**
              * Sets the velocity for the molecule to the given value.  All
              * atoms contained in the molecule will have the same velocity.
              * This method is exposing glotzmd::Polymer::SetVelocity().
              * @param velocity Molecule's resultant velocity
              * @todo Take an IAPIVector here and check the dimension.
              */
            void setVelocity(GlotzillaVector *velocity);
            /**
              * Modifies the velocity for the molecule by the given value.
              * All atoms contained in the molecule will be modified by the
              * same value.
              * This method is exposing glotzmd::Polymer::ModifyVelocity().
              * @param velocity Value by which to change the molecule's velocity
              * @todo Take an IAPIVector here and check the dimension.
              */
            void modifyVelocity(GlotzillaVector *velocity);
            /**
              * Scales(multiplies) the velocity for the molecule by the
              * given value.  All atoms contained in the molecule will be
              * multiplied by the same value.
              * This method is exposing glotzmd::Polymer::RescaleVelocity().
              * @param velocity Value by which to scale the molecule's velocity
              * @todo Take an IAPIVector here and check the dimension.
              */
            void rescaleVelocity(double velocity);
            /**
              * Multiplies the velocity for the molecule by -1, thus just
              * chaning the sign of the velocity.  All atoms contained in the
              * molecule will have its velocity inverted. 
              * This method is exposing glotzmd::Polymer::InvertVelocity().
              */
            void invertVelocity();
            /**
              * This method is exposing glotzmd::Polymer::SetPosition().
              */
            void setPosition(GlotzillaVector *velocity);
            /**
              * This method is exposing glotzmd::Polymer::SetPositionInBox().
              */
            void setPositionInBox(GlotzillaVector *velocity);
           /**
             * WARNING : This method should not be called outside of the
             *           glue layer implementation.
             * @return Returns the Glotzilla native object (glotzmd::Polymer)
             *         that this instance is holding.
             */
            virtual glotzmd::Particle *getGlotzParticle();

        protected:
            glotzmd::Polymer *glotzPolymer;

        private:
            void init();
            void init(glotzmd::Polymer *p);
            ObjectManager *objectManager;

    };
}
#endif
