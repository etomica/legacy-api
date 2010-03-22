/*
 *  GlotzillaBoxEventManager.h
 *  API Glue
 *
 */

#ifndef GLOTZ_BOXEVENTMGR_WRAPPER_H
#define GLOTZ_BOXEVENTMGR_WRAPPER_H

#include <vector>

#include "IAPIBoxEventManager.h"
#include "IAPIBoxListener.h"

using namespace molesimAPI;

namespace glotzwrappers
{

    class GlotzillaBoxEventManager : public virtual IAPIBoxEventManager {

        public:
            void addListener(IAPIBoxListener *listener);
            /**
              * This method is not implemented.
              */
            void removeListener(IAPIBoxListener *listener);

            // Non-API
            /**
              * Method called when an atom is added to a box.
              * @param box Box the atom was added to.
              * @param atom Atom added to the box.
              */
            void atomAdded(IAPIBox *box, IAPIAtom *atom);
            /**
              * Method called when an atom is removed from a box.
              * @param box Box the atom was removed from.
              * @param atom Atom removed from the box.
              */
            void atomRemoved(IAPIBox *box, IAPIAtom *atom);
            /**
              * Method called when a molecule is added to a box.
              * @param box Box the molecule was added to.
              * @param molecule Molecule added to the box.
              */
            void moleculeAdded(IAPIBox *box, IAPIMolecule *molecule);
            /**
              * Method called when a molecule is removed from a box.
              * @param box Box the molecule was removed from.
              * @param molecule Molecule removed from the box.
              */
            void moleculeRemoved(IAPIBox *box, IAPIMolecule *molecule);
            /**
              * Method called when an atom's index within the box has
              * changed. 
              * @param box Box containing the atom which index changed.
              * @param index New index for the atom.
              */
            void globalAtomIndexChanged(IAPIBox *box, int index);
            void globalAtomLeafIndexChanged(IAPIBox *box, int index);
            /**
              * Method called when an atom's leaf index within the box has
              * changed. 
              * @param box Box containing the atom which leaf index changed.
              * @param index New leaf index for the atom.
              */
            void atomLeafIndexChanged(IAPIBox *box, IAPIAtom *atom, int index);
            void numberMolecules(IAPIBox *box, IAPISpecies *species, int count);
            /**
              * Method called when a molecule's index within the box has
              * changed. 
              * @param box Box containing the molecule which index changed.
              * @param molecule Molecule which index changed.
              * @param index New index for the atom.
              */
            void moleculeIndexChanged(IAPIBox *box, IAPIMolecule *molecule, int index);

        protected:
            std::vector<IAPIBoxListener *> listeners;
    };
}

#endif
