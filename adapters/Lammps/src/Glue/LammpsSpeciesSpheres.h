/*
 *  LammpsSpeciesSpheres.h
 *  API Glue
 *
 */

#ifndef LAMMPS_SPECIESSPHERES_WRAPPER_H
#define LAMMPS_SPECIESSPHERES_WRAPPER_H

#include <vector>

#include "IAPISpecies.h"
#include "IAPIAtomType.h"
#include "LammpsInterfaceConformation.h"
#include "IAPISimulation.h"
#include "LammpsSpecies.h"
#include "LammpsAtomTypeSphere.h"
#include "LammpsNativeConformation.h"

using namespace molesimAPI;

namespace lammpswrappers
{

    class LammpsSpeciesSpheres : public LammpsSpecies, public virtual IAPISpecies {

        public:
            /**
              * Create a species.  Does not specify a conformation.
              * @param sim Simulation that contains the species.
              */
            LammpsSpeciesSpheres(IAPISimulation *sim);
            /**
              * Create a species.
              * @param sim Simulation that contains the species.
              * @param conform A conformation (see intitializeConformation)
              *                that will be used to set the position of
              *                atoms within the molecule.
              */
            LammpsSpeciesSpheres(IAPISimulation *sim, LammpsInterfaceConformation *conform);

            // API compliant methods
            /**
              * Build a molecule of this species.  The molecule is an
              * instance of a LammpsMolecule.
              * @return Returns the molecule constructed.
              */
            IAPIMolecule *makeMolecule();

            // Non-API  methods
            /**
              * Add an atom type to the species atom type list used for
              * molecule creation.
              * @param type atom type to add to list.
              * @param nAtoms Number of atoms, of given type, to constuct in
              *               a molecule of this type.
              */
            void addChildType(IAPIAtomType *type, int nAtoms);
            /**
              * Build a molecule of this species.  The molecule is an
              * instance of a LammpsMolecule.
              * NOTE : Can only construct a monatomic molecule with this
              *        method.
              * @param The leaf index of the atom within the molecule
              * @return Returns the molecule constructed.
              */
            IAPIMolecule *makeMolecule(int leafIndex);

    };
}

#endif
