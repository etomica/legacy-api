/*
 *  GlotzillaBoxAtomEvent.cpp
 *  API Glue
 *
 */

#include "stdio.h"

#include "GlotzillaBoxAtomEvent.h"

namespace glotzwrappers
{

    GlotzillaBoxAtomEvent::GlotzillaBoxAtomEvent(IAPIAtom *atom, IAPIBox *box) :
                                               GlotzillaBoxEvent(box) {
        mAtom = atom;
    }

    /*
     * getAtom()
     */
    IAPIAtom *GlotzillaBoxAtomEvent::getAtom() {
        return mAtom;
    }

}
