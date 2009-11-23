/*
 *  TowheeSpeciesSpheresHetero.h
 *  API Glue
 *
 */

#ifndef TOWHEE_SPECIESHETERO_WRAPPER_H
#define TOWHEE_SPECIESHETERO_WRAPPER_H

#include <vector>

#include "IAPIAtomType.h"
#include "IAPIMolecule.h"
#include "TowheeSpecies.h"
#include "TowheeSimulationSniffer.h"

using namespace molesimAPI;

namespace towheesnifferwrappers
{

    class TowheeSpeciesSpheresHetero : public TowheeSpecies {

        public:
            TowheeSpeciesSpheresHetero(TowheeSimulationSniffer *sim);

            // API compliant methods
            virtual IAPIMolecule *makeMolecule();
            virtual IAPIMolecule *makeMolecule(int mID);

            // Non-API compliant methods
            void addAtomType(IAPIAtomType *atomType);

        private:
    };
}

#endif
