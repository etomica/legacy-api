/*
 *  TowheeAtomType
 *  API Glue
 *
 */

#ifndef TOWHEE_ATOMTYPE_WRAPPER_H
#define TOWHEE_ATOMTYPE_WRAPPER_H

#include "IAPIAtomType.h"
#include "IAPIElement.h"
#include "IAPISpecies.h"

using namespace molesimAPI;

namespace towheewrappers
{

    class TowheeAtomType : public virtual IAPIAtomType {

        public:

            TowheeAtomType(int index);

            void setIndex(int newIndex);
            int getIndex();
            void setSpecies(IAPISpecies *newParent);
            IAPISpecies *getSpecies();
            void setChildIndex(int newChildIndex);
            int getChildIndex();
            double getMass();
            double rm();
            IAPIElement *getElement();

        protected:
            IAPIElement *mElement;

        private:
            int mIndex;
    };
}
#endif
