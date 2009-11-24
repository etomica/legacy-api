/*
 *  TowheeSpeciesSpheresMono.h
 *  API Glue
 *
 */

#ifndef TOWHEE_SPECIESMONO_WRAPPER_H
#define TOWHEE_SPECIESMONO_WRAPPER_H

#include "IAPIAtomType.h"
#include "IAPIMolecule.h"
#include "TowheeSpecies.h"
#include "TowheeSimulationSniffer.h"

using namespace molesimAPI;

namespace towheesnifferwrappers
{

    class TowheeSpeciesSpheresMono : public TowheeSpecies {

        public:
            TowheeSpeciesSpheresMono(TowheeSimulationSniffer *sim, IAPIAtomType *aType);

            // API compliant methods
            virtual IAPIMolecule *makeMolecule();

        private:
            IAPIAtomType *mAtomType;
    };
}

#endif
