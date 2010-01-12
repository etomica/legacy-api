/*
 *  LammpsMoleculeList.h
 *  API Glue
 *
 */

#ifndef LAMMPS_MOLECULE_LIST_WRAPPER_H
#define LAMMPS_MOLECULE_LIST_WRAPPER_H

#include <vector>

#include "IAPIMolecule.h"
#include "IAPIMoleculeList.h"

using namespace molesimAPI;

namespace lammpssnifferwrappers
{

    class LammpsMoleculeList : public virtual IAPIMoleculeList {
        public:
            LammpsMoleculeList();

            // API Compliance
            int getMoleculeCount();			
            IAPIMolecule *getMolecule(int);

            // Non-API methods
            void addMolecule(IAPIMolecule *);
            void removeMolecule(IAPIMolecule *);
            void clear();

        protected:
            std::vector<IAPIMolecule *> mMolecule;
    };
}
#endif
