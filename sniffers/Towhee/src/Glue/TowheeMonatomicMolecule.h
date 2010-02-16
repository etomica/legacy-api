/*
 *  TowheeMonatomicMolecule.h
 *  API Glue
 *
 *
 */

#ifndef TOWHEE_MONATOMICMOLECULE_WRAPPER_H
#define TOWHEE_MONATOMICMOLECULE_WRAPPER_H

#include "IAPIAtom.h"
#include "IAPIBox.h"
#include "IAPISpecies.h"

#include "TowheeAtomList.h"
#include "TowheeMolecule.h"

using namespace molesimAPI;

namespace towheesnifferwrappers
{

    class TowheeMonatomicMolecule : public TowheeMolecule {

        public:
            TowheeMonatomicMolecule(IAPISpecies *species, IAPIBox *box);

            // API Compliance
            virtual void addChildAtom(IAPIAtom *atom);
            virtual void removeChildAtom(IAPIAtom *atom);
            IAPIAtomList *getChildList();

        private:
            TowheeAtomList *mAtoms;
    };
}
#endif
