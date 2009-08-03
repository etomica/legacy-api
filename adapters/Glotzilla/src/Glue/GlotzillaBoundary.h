
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
              * Constructor for GlotizllaBoundary.  GlotzillaBoundary is
              * a purely virtual class and the constructor is only called
              * from its subclasses.
              * @param sim Simulation that the boundary belongs to.
              */
            GlotzillaBoundary(IAPISimulation *sim);

            // API Compliance
            /**
              * Scales the boundary dimensions such that the boundary would be
              * inscribed within a rectangle of the given size.  For a
              * rectangular boundary, this simply sets the boundary length in
              * each dimension.  Specific interpretation of the given values
              * for non-rectangular shapes depends on the subclass.
              * @param v boundary length in each dimension
              */
            void setBoxSize(IAPIVector *v);
            /**
              * @return Returns the length of the boundary in each dimension
              *         that the boundary would be inscribed in.
              */
            IAPIVector *getBoxSize();
            /**
              * @return Returns the volume enclosed by the boundary.
              */
            double volume();
            /**
              * The nearest image is the pair of atom images that are closest
              * when all periodic-boundary images are considered.
              *
              * If the vector passed to this method is the displacement vector
              * between two points, the vector will be transformed such that
              * it corresponds to the vector between the nearest image of
              * those two points.
              * @todo Try to make this methods documentation easier to
              *       understand.
              */
            virtual void nearestImage(IAPIVectorMutable *v) = 0;
            /**
              * Determines the translation vector needed to apply a periodic-image
              * transformation that moves the given point to an image point within the
              * boundary (if it lies outside, in a direction subject to periodic
              * imaging).
              * 
              * @param r
              *            vector position of untransformed point; r is not changed by
              *            this method
              * @return the displacement that must be applied to r to move it to its
              *         central-image location
              * @todo Try to make this methods documentation easier to
              *       understand.
              */
            virtual IAPIVector *centralImage(IAPIVector *v) = 0;
            /**
              * Sets the box that holds this boundary.
              * @param box Box that holds the boundary.
              */
            void setBox(IAPIBox *box);
            /**
              * @return Returns the box that holds the boundary.  If the
              *         boundary is not owned by a box, null is returned.
              */
            IAPIBox *getBox();
            /**
              * @todo Document this method. Refer to notes from early Jan
              *       2009.
              */
            virtual IAPIVector *getEdgeVector(int d) = 0;
            /**
              * Returns true if the bounday is periodic in the given
              * dimension.
              * @param d dimension to consider periodicity
              * @return Returns the periodicity for the dimension.
              */
            virtual bool getPeriodicity(int d) = 0;
            /**
              * @return Returns the center position of the boundary.
              */
            IAPIVector *getCenter();
            /**
              * @return Returns the event manager for the boundary.
              */
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
