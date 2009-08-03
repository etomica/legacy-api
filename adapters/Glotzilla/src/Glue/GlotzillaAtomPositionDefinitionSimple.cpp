/*
 *  GlotzillaAtomPositionDefinitionSimple.cpp
 *  API Glue
 *
 */

#include <glotzmd.h>

#include "IAPIAtomPositioned.h"
#include "IAPIAtomList.h"

#include "GlotzillaAtomPositionDefinitionSimple.h"
#include "GlotzillaAtom.h"

namespace glotzwrappers
{

    /*
     * position()
     */
    IAPIVector *GlotzillaAtomPositionDefinitionSimple::position(IAPIMolecule *atom) {
        IAPIMolecule *mole = atom;
        IAPIAtomList *as = mole->getChildList();
        IAPIAtom *a = as->getAtom(0);
        return (dynamic_cast<GlotzillaAtom *>(a)->getPosition());
    }
}

