/*
 *  IAPIBoundary.h
 *  API Glue
 *
 */

#ifndef API_IBOUNDARY_WRAPPER_H
#define API_IBOUNDARY_WRAPPER_H

#include "IAPIBoundaryEventManager.h"
#include "IAPIVector.h"
#include "IAPIVectorMutable.h"

namespace molesimAPI
{

    // Declared instead of included as IAPIBox appears AFTER
    // IAPIBoundary in the apisim.i file.
    class IAPIBox;

    class IAPIBoundary {

        public:
            /**
              * @return Returns the length of the boundary in each dimension
              *         that the boundary would be inscribed in.
              */
            virtual IAPIVector *getBoxSize() = 0;
            /**
              * Scales the boundary dimensions such that the boundary would be
              * inscribed within a rectangle of the given size.  For a
              * rectangular boundary, this simply sets the boundary length in
              * each dimension.  Specific interpretation of the given values
              * for non-rectangular shapes depends on the subclass.
              * @param v boundary length in each dimension
              */
            virtual void setBoxSize(IAPIVector *v) = 0;
            /**
              * @return Returns the volume enclosed by the boundary.
              */
            virtual double volume() = 0;
            /**
              * The nearest image is the pair of atom images that are closest
              * when all periodic-boundary images are considered.
              *
              * If the vector passed to this method is the displacement vector
              * between two points, the vector will be transformed such that
              * it corresponds to the vector between the nearest image of
              * those two points.
              */
            virtual void nearestImage(IAPIVectorMutable *) = 0;
            /**
              * Determines the translation vector needed to apply a periodic-image
              * transformation that moves the given point to an image point within the
              * boundary (if it lies outside, in a direction subject to periodic
              * imaging).
              * 
              * @param r vector position of untransformed point; r is not changed by
              *          this method
              * @return the displacement that must be applied to r to move it to its
              *         central-image location
              */
            virtual IAPIVector *centralImage(IAPIVector *) = 0;
            /**
              * Sets the box that holds this boundary.
              * @param box Box that holds the boundary.
              */
            virtual void setBox(IAPIBox *) = 0;
            /**
              * @return Returns the box that holds the boundary.  If the
              *         boundary is not owned by a box, null is returned.
              */
            virtual IAPIBox *getBox() = 0;
            /**
              * @param d Dimension to return edge vector for
              * @return Returns the vector that defines the edge of this
              *         boundary for the given dimension.  All vectors
              *         returned by this method can be considered to
              *         originate from one corner.
              */
            virtual IAPIVector *getEdgeVector(int d) = 0;
            /**
              * @return Returns the center position of the boundary.
              */
            virtual IAPIVector *getCenter() = 0;
            /**
              * Returns true if the bounday is periodic in the given
              * dimension.
              * @param d dimension to consider periodicity
              * @return Returns the periodicity for the dimension.
              */
            virtual bool getPeriodicity(int d) = 0;
            /**
              * @return Returns the event manager for the boundary.
              */
            virtual IAPIBoundaryEventManager *getEventManager() = 0;
    };
}
#endif
