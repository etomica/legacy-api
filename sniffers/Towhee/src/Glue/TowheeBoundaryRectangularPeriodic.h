
/*
 *  TowheeBoundaryRectangularPeriodic.h
 *  API Glue
 *
 */

#ifndef TOWHEE_BOUNDARY_RECTANUGLAR_PERIODIC_WRAPPER_H
#define TOWHEE_BOUNDARY_RECTANUGLAR_PERIODIC_WRAPPER_H

#include "IAPIVector.h"
#include "IAPIVectorMutable.h"
#include "TowheeBoundary.h"
#include "TowheeSpace.h"

using namespace molesimAPI;

namespace towheesnifferwrappers
{

    class TowheeBoundaryRectangularPeriodic : public TowheeBoundary {

        public:

            TowheeBoundaryRectangularPeriodic(TowheeSpace *space);

            virtual void nearestImage(IAPIVectorMutable *v);
            virtual IAPIVector *centralImage(IAPIVector *v);
            virtual IAPIVector *getEdgeVector(int d);
            virtual bool getPeriodicity(int d);

    };
}

#endif
