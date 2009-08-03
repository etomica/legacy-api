/*
 *  LammpsAtomList.h
 *  API Glue
 *
 */

#ifndef LAMMPS_ATOMLIST_WRAPPER_H
#define LAMMPS_ATOMLIST_WRAPPER_H

#include <vector>

#include "IAPIAtom.h"
#include "IAPIAtomList.h"

using namespace molesimAPI;

namespace lammpswrappers
{

    class LammpsAtomList : public virtual IAPIAtomList {
        public:
            LammpsAtomList();

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
