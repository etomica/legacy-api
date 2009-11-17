/*
 *  TowheeAtomList.h
 *  API Glue
 *
 */

#ifndef TOWHEE_ATOMLIST_WRAPPER_H
#define TOWHEE_ATOMLIST_WRAPPER_H

#include <vector>

#include "IAPIAtom.h"
#include "IAPIAtomList.h"

using namespace molesimAPI;

namespace towheesnifferwrappers
{

    class TowheeAtomList : public virtual IAPIAtomList {
        public:
            int getAtomCount();			
            IAPIAtom *getAtom(int i);

            // Non-API methods
            void addChildAtom(IAPIAtom *atom);

        private:
            std::vector<IAPIAtom *>mAtoms;
    };
}
#endif
