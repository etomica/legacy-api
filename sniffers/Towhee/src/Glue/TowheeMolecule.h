/*
 *  TowheeMolecule.h
 *  API Glue
 *
 */

#ifndef TOWHEE_MOLECULE_WRAPPER_H
#define TOWHEE_MOLECULE_WRAPPER_H

#include "IAPIAtom.h"
#include "IAPIAtomList.h"
#include "IAPIBox.h"
#include "IAPISpecies.h"
#include "IAPIMolecule.h"

using namespace molesimAPI;

namespace towheesnifferwrappers
{

    class TowheeMolecule : public virtual IAPIMolecule {

        public:
            TowheeMolecule(IAPIBox *box);

            virtual int getIndex();
            virtual void setIndex(int);
            virtual void addChildAtom(IAPIAtom *atom) = 0;
            virtual void removeChildAtom(IAPIAtom *atom) = 0;
            virtual IAPIAtomList *getChildList() = 0;
            virtual IAPISpecies *getType();

            // Non-API
            void setBox(IAPIBox *box);
            IAPIBox *getBox();

        protected:
            IAPISpecies *mSpecies;
            int mIndex;

        private:
            IAPIBox *mBox;
    };
}
#endif
