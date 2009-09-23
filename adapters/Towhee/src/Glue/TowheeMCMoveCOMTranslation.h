/*
 *  TowheeMCMoveCOMTranslation.h
 *  API Glue
 *
 */

#ifndef TOWHEE_MC_MOVE_COM_TRANSLATION_WRAPPER_H
#define TOWHEE_MC_MOVE_COM_TRANSLATION_WRAPPER_H

#include "IAPISpeciesManager.h"
#include "TowheeMCMove.h"

using namespace molesimAPI;

namespace towheewrappers
{

    class TowheeMCMoveCOMTranslation : public virtual TowheeMCMove {

        public:

            TowheeMCMoveCOMTranslation(IAPISpeciesManager *sm, double p);

            // Non-API methods
            void setPmtcmt(double values[]);
            void setRmtrac(double value);
            void setTatrac(double value);
            virtual void setup();

        private:
            IAPISpeciesManager *mSpeciesMgr;
            double *pmtcmt;
            double rmtrac;
            double tatrac;
    };
}

#endif
