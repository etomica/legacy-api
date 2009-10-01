/*
 *  TowheeSpeciesSpheresMono.h
 *  API Glue
 *
 */

#ifndef TOWHEE_SPECIESMONO_WRAPPER_H
#define TOWHEE_SPECIESMONO_WRAPPER_H

#include "IAPIAtomType.h"
#include "IAPIBoundary.h"
#include "IAPIMolecule.h"
#include "TowheeSimulation.h"
#include "TowheeSpecies.h"

using namespace molesimAPI;

namespace towheewrappers
{

    class TowheeSpeciesSpheresMono : public TowheeSpecies {

        public:
            TowheeSpeciesSpheresMono(TowheeSimulation *sim, IAPIAtomType *aType,
                                     IAPIBoundary *boundary);

            // API compliant methods
            virtual IAPIMolecule *makeMolecule();

        private:
            IAPIAtomType *mAtomType;
            IndexManager *mAtomIDMgr;
            IndexManager *mMoleIDMgr;
            IAPIBoundary *mBoundary;
    };
}

#endif
