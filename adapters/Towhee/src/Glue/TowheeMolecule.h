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
#include "IAPISimulation.h"
#include "IAPISpecies.h"
#include "IAPIMolecule.h"

using namespace molesimAPI;

namespace towheewrappers
{

    class TowheeMolecule : public virtual IAPIMolecule {

        public:
            TowheeMolecule() {};

            virtual int getIndex();
            virtual void setIndex(int);
            virtual void addChildAtom(IAPIAtom *atom) = 0;
            virtual void removeChildAtom(IAPIAtom *atom) = 0;
            virtual IAPIAtomList *getChildList() = 0;
            virtual IAPISpecies *getType();

            // Non-API
            /**
              * The molecule holds a handle to the box that it is inside.
              * @param box Box as described above.
              */
            void setBox(IAPIBox *box);
            /**
              * @return Returns the box that the molecule is inside.
              */
            IAPIBox *getBox();

        protected:
            IAPISpecies *mSpecies;
            int mIndex;
            IAPIBox *mBox;

    };
}
#endif
