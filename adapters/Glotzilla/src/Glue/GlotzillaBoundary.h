
/*
 *  GlotzillaBoundary.h
 *  API Glue
 *
 */

#ifndef GLOTZ_BOUNDARY_WRAPPER_H
#define GLOTZ_BOUNDARY_WRAPPER_H

#include <string>
#include <glotzmd.h>

#include "IAPIBoundary.h"
#include "IAPIBoundaryEventManager.h"
#include "IAPISimulation.h"
#include "IAPIVector.h"
#include "IAPIVectorMutable.h"
#include "GlotzillaSpace.h"
#include "GlotzillaVector.h"

using namespace molesimAPI;

namespace glotzwrappers
{

    /**
      * GlotzillaBoundary is used as a superclass for specific boundary
      * classes.  The boundary describes the size and periodic nature of a
      * box's boundaries.
      */
    class GlotzillaBoundary : public virtual IAPIBoundary {

        public:
            /**
              * Constructor for GlotzillaBoundary.  GlotzillaBoundary is
              * a purely virtual class and the constructor is only called
              * from its subclasses.
              * @param sim Simulation that the boundary belongs to.
              */
            GlotzillaBoundary(IAPISimulation *sim);

            // API Compliance
            void setBoxSize(IAPIVector *v);
            IAPIVector *getBoxSize();
            double volume();
            virtual void nearestImage(IAPIVectorMutable *v) = 0;
            virtual IAPIVector *centralImage(IAPIVector *v) = 0;
            void setBox(IAPIBox *box);
            IAPIBox *getBox();
            virtual IAPIVector *getEdgeVector(int d) = 0;
            virtual bool getPeriodicity(int d) = 0;
            IAPIVector *getCenter();
            IAPIBoundaryEventManager *getEventManager();

            // Non-API methods
            /**
              * WARNING : This method should NOT be called outside of the
              *           glue layer implementation.
              * @return Returns the glotzaimapi::BoundaryConditions object
              * that this boundary object holds.
              */
            glotzsimapi::BoundaryConditions *getGlotzillaBoundary() {return mBoundaryConditions;}

        protected:
            glotzsimapi::BoundaryConditions* mBoundaryConditions;
            GlotzillaVector *mVector;
            GlotzillaVector *mCenter;
            IAPIBox *mBox;
            GlotzillaSpace *mSpace;
            IAPIBoundaryEventManager *mEventManager;
    };
}

#endif
