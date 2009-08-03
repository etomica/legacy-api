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
          virtual IAPIVector *getBoxSize() = 0;
          virtual void setBoxSize(IAPIVector *) = 0;
          virtual double volume() = 0;
          virtual void nearestImage(IAPIVectorMutable *) = 0;
          virtual IAPIVector *centralImage(IAPIVector *) = 0;
          virtual void setBox(IAPIBox *) = 0;
          virtual IAPIBox *getBox() = 0;
          virtual IAPIVector *getEdgeVector(int d) = 0;
          virtual IAPIVector *getCenter() = 0;
          virtual bool getPeriodicity(int d) = 0;
          virtual IAPIBoundaryEventManager *getEventManager() = 0;
    };
}
#endif
