/*
 *  TowheeSimulationSniffer.h
 *  API Glue
 *
 */

#ifndef TOWHEE_SIMULATION_SNIFFER_WRAPPER_H
#define TOWHEE_SIMULATION_SNIFFER_WRAPPER_H

#include "IAPISimulation.h"
#include "TowheeAtomTypeSphere.h"
#include "TowheeSimulation.h"

using namespace molesimAPI;

namespace towheesnifferwrappers
{

    class TowheeSimulationSniffer : public TowheeSimulation,
                                    public virtual IAPISimulation {

        public:

            TowheeSimulationSniffer(char *inputFile);

            // Non-API methods
            void sniff();

        private:
            void sniffBoxes();
            void sniffMolecules(TowheeAtomTypeSphere **atomType);
            void sniffSpecies(TowheeAtomTypeSphere **atomType);
            int sniffAtomTypes();
    };
}

#endif
