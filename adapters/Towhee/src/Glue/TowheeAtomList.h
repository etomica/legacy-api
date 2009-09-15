/*
 *  TowheeAtomList.h
 *  API Glue
 *
 */

#ifndef TOWHEE_ATOM_LIST_WRAPPER_H
#define TOWHEE_ATOM_LIST_WRAPPER_H

#include <vector>

#include "IAPIAtom.h"
#include "IAPIAtomList.h"

using namespace molesimAPI;

namespace towheewrappers
{

    class TowheeAtomList : public virtual IAPIAtomList {
        public:
            TowheeAtomList();

            // API Compliance
            int getAtomCount();			
            IAPIAtom *getAtom(int);

            // Non-API methods
            void addAtom(IAPIAtom *);
            void removeAtom(IAPIAtom *);
            void clear();

        protected:
            std::vector<IAPIAtom *> mAtom;
    };
}
#endif
