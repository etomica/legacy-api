/*
 *  TowheeBoxEventManager.h
 *  API Glue
 *
 */

#ifndef TOWHEE_BOXEVENTMGR_WRAPPER_H
#define TOWHEE_BOXEVENTMGR_WRAPPER_H

#include <vector>

#include "IAPIBoxEventManager.h"
#include "IAPIBoxListener.h"

using namespace molesimAPI;

namespace towheesnifferwrappers
{

    class TowheeBoxEventManager : public virtual IAPIBoxEventManager {

        public:
            void addListener(IAPIBoxListener *listener);
            void removeListener(IAPIBoxListener *listener);

            // Non-API
            void atomAdded(IAPIBox *box, IAPIAtom *atom);
            void atomRemoved(IAPIBox *box, IAPIAtom *atom);
            void moleculeAdded(IAPIBox *box, IAPIMolecule *molecule);
            void moleculeRemoved(IAPIBox *box, IAPIMolecule *molecule);
            void globalAtomIndexChanged(IAPIBox *box, int index);
            void globalAtomLeafIndexChanged(IAPIBox *box, int index);
            void atomLeafIndexChanged(IAPIBox *box, IAPIAtom *atom, int index);
            void numberMolecules(IAPIBox *box, IAPISpecies *species, int count);
            void moleculeIndexChanged(IAPIBox *box, IAPIMolecule *molecule, int index);

    };
}

#endif
