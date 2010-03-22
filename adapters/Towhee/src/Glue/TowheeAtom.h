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
#include "IAPIBoundary.h"
#include "IAPISimulation.h"
#include "IAPIVector.h"
#include "IAPIVectorMutable.h"
#include "TowheeVector3DAtom.h"

using namespace molesimAPI;

namespace towheewrappers
{

    class TowheeAtom : public virtual IAPIAtom,
                          public virtual IAPIAtomKinetic {

        public:
            /**
              * TowheeAtom is an atom the represents a physical atom with
              * a position.  Towhee atom's do not have a velocity.
              * @param at The atom type of this atom.
              * @param tIndex The index used to get info about the atom when
              *               reaching into the native Towhee simulation.
              */
            TowheeAtom(IAPIAtomType *at, int tIndex);

            int getIndex();
            void setIndex(int index);
            void setLeafIndex(int newLeafIndex);
            int getLeafIndex();
            IAPIVectorMutable *getPosition();
            /**
              * Towhee atom's do not have a velocity.  This method is not
              * implemented.
              * @return NULL
              */
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
