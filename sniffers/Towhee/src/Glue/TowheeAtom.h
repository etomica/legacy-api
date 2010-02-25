/*
 *  TowheeAtom.h
 *  API Glue
 *
 */

#ifndef TOWHEE_ATOM_WRAPPER_H
#define TOWHEE_ATOM_WRAPPER_H

#include "IAPIAtom.h"
#include "IAPIAtomKinetic.h"
#include "IAPIAtomType.h"
#include "IAPIBox.h"
#include "IAPIMolecule.h"
#include "IAPIVectorMutable.h"
#include "TowheeVector3DAtom.h"

using namespace molesimAPI;

namespace towheesnifferwrappers
{

    class TowheeAtom : public virtual IAPIAtom,
                          public virtual IAPIAtomKinetic {

        public:

            TowheeAtom(IAPIAtomType *at, IAPIBox *box, int tIndex);

            int getIndex();
            void setIndex(int index);
            void setLeafIndex(int newLeafIndex);
            int getLeafIndex();
            IAPIVectorMutable *getPosition();
            IAPIVectorMutable *getVelocity();
            void setParent(IAPIMolecule *newParent);
            IAPIMolecule *getParentGroup();
            IAPIAtomType *getType();

            // Non-API
            void setSnifferMolecule(IAPIMolecule *parent);

        private:
            IAPIAtomType *mAtomType;
            IAPIMolecule *mParent;
            int mLeafIndex;
            int mIndex;
            TowheeVector3DAtom *mPosition;
    };
}
#endif
