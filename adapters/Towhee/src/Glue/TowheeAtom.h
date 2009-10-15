/*
 *  TowheeAtom.h
 *  API Glue
 *
 */

#ifndef TOWHEE_ATOM_WRAPPER_H
#define TOWHEE_ATOM_WRAPPER_H

#include "IAPIAtom.h"
#include "IAPIAtomPositioned.h"
#include "IAPIAtomKinetic.h"
#include "IAPIAtomType.h"
#include "IAPIBoundary.h"
#include "IAPISimulation.h"
#include "IAPIVector.h"
#include "IAPIVectorMutable.h"
#include "TowheeVector3DAtom.h"

using namespace molesimAPI;

namespace towheewrappers
{

    class TowheeAtom : public virtual IAPIAtom,
                          public virtual IAPIAtomPositioned,
                          public virtual IAPIAtomKinetic {

        public:

            TowheeAtom(IAPIAtomType *at, int tIndex);

            int getIndex();
            void setIndex(int index);
            void setLeafIndex(int newLeafIndex);
            int getLeafIndex();
            IAPIVectorMutable *getPosition();
            IAPIVectorMutable *getVelocity();
            void setParent(IAPIMolecule *newParent);
            IAPIMolecule *getParentGroup();
            IAPIAtomType *getType();

        private:
            IAPIAtomType *mAtomType;
            IAPIMolecule *mParent;
            int mLeafIndex;
            int mIndex;
            int mTowheeIndex;
            TowheeVector3DAtom *mPosition;
    };
}
#endif
