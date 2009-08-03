/*
 *  GlotzillaBoundaryPeriodic.h
 *  API Glue
 *
 */

#ifndef GLOTZ_BOUNDARYPERIODIC_WRAPPER_H
#define GLOTZ_BOUNDARYPERIODIC_WRAPPER_H

#include <string>
#include <glotzmd.h>

#include "IAPIVector.h"
#include "IAPIVectorMutable.h"

#include "GlotzillaBoundary.h"
#include "GlotzillaVector3D.h"

using namespace molesimAPI;

namespace glotzwrappers
{

    /**
      * GlotzillaBoundaryPeriodic is a rectangular boundary that is periodic
      * in all dimensions.  It holds a Glotzilla native boundary
      * (glotzsimapi::PeriodicBoundary).
      */
    class GlotzillaBoundaryPeriodic : public GlotzillaBoundary {

        public:
            /**
              * Constructor for GlotzillaBoundaryPeriodic.  The boundary
              * holds a new instance of a glotzsimapi::PeriodicBoundary.
              * @param sim Simulation that the boundary blongs to.
              */
            GlotzillaBoundaryPeriodic(IAPISimulation *sim);
            /**
              * Constructor for GlotzillaBoundaryPeriodic.  The boundary
              * holds the glotzsimapi::PeriodicBoundary that is passed in.
              * @param sim Simulation that the boundary blongs to.
              * @param boundaryConditions The glotzsimapi::PeriodicBoundary
              *                           that the boundary holds.
              */
            GlotzillaBoundaryPeriodic(IAPISimulation *sim,
                       glotzsimapi::PeriodicBoundary *boundaryConditions);

            // API Compliance
            virtual void nearestImage(IAPIVectorMutable *v);
            virtual IAPIVector *centralImage(IAPIVector *v);
            void setBoxSize(IAPIVector *v);
            virtual IAPIVector *getEdgeVector(int d);
            virtual bool getPeriodicity(int d);

            // Non-API methods

        protected:
            IAPIVectorMutable *dimensions;
            IAPIVectorMutable *dimensionsHalf;
    };
}

#endif
