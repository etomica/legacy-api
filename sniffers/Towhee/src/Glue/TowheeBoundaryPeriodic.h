/*
 *  TowheeBoundaryPeriodic.h
 *  API Glue
 *
 */

#ifndef TOWHEE_BOUNDARYPERIODIC_WRAPPER_H
#define TOWHEE_BOUNDARYPERIODIC_WRAPPER_H

#include "IAPIVector.h"
#include "IAPIVectorMutable.h"
#include "TowheeBoundary.h"

using namespace molesimAPI;

namespace towheesnifferwrappers
{

    class TowheeBoundaryPeriodic : public TowheeBoundary {

        public:
            virtual void nearestImage(IAPIVectorMutable *v);
            virtual IAPIVector *centralImage(IAPIVector *v);
            void setDimensions(IAPIVector *v);
            virtual IAPIVector *getEdgeVector(int d);
            virtual bool getPeriodicity(int d);

    };
}

#endif
