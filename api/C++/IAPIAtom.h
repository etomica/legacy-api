/*
 *  IAPIAtom.h
 *  API Glue
 *
 */

#ifndef API_IATOM_WRAPPER_H
#define API_IATOM_WRAPPER_H

namespace molesimAPI
{

    class IAPIBox;
    class IAPIMolecule;
    class IAPIAtomType;

    class IAPIAtom {

        public:
            virtual int getIndex() = 0;
            virtual void setIndex(int) = 0;
            virtual void setLeafIndex(int) = 0;
            virtual int getLeafIndex() = 0;
            virtual void setParent(IAPIMolecule *newParent) = 0;
            virtual IAPIMolecule *getParentGroup() = 0;
            virtual IAPIAtomType *getType() = 0;
    };
}
#endif
