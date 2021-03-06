/*
 *  TowheeSpecies.h
 *  API Glue
 *
 */

#ifndef TOWHEE_SPECIES_WRAPPER_H
#define TOWHEE_SPECIES_WRAPPER_H

#include <vector>

#include "IAPISpecies.h"
#include "IAPIAtomType.h"
#include "IAPIMolecule.h"
#include "TowheeSimulationSniffer.h"
#include "TowheeInterfaceConformation.h"

using namespace molesimAPI;

namespace towheesnifferwrappers
{

    /**
      * @todo Description of TowheeSpecies here.
      */
    class TowheeSpecies : public virtual IAPISpecies {

        public:

            TowheeSpecies(TowheeSimulationSniffer *sim);
            virtual int getIndex();
            virtual void setIndex(int index);
            virtual IAPIMolecule *makeMolecule() = 0;
            int getAtomTypeCount();
            IAPIAtomType *getAtomType(int index);
            void initializeConformation(IAPIMolecule *molecule);

            // Non-API methods
            void setConformation(TowheeInterfaceConformation *c);

        protected:
            std::vector<IAPIAtomType *> mTypeList;
            TowheeSimulationSniffer *mSim;

        private:
            int mIndex;
            TowheeInterfaceConformation *mConformation;
    };
}

#endif
