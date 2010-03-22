
/*
 *  TowheeBoundary.h
 *  API Glue
 *
 */

#ifndef TOWHEE_BOUNDARY_WRAPPER_H
#define TOWHEE_BOUNDARY_WRAPPER_H

#include "IAPIBoundary.h"
#include "IAPIBoundaryEventManager.h"
#include "IAPISimulation.h"
#include "IAPIVector.h"
#include "IAPIVectorMutable.h"

#include "TowheeSpace.h"

using namespace molesimAPI;

namespace towheewrappers
{

    class TowheeBoundary : public virtual IAPIBoundary {

        public:

            /**
              * Constructor for LammpsBoundary.  LammpsBoundary is
              * a purely virtual class and the constructor is only called
              * from its subclasses.
              * @param space The space that should be used to generate
              *              vectors.
              */
            TowheeBoundary(TowheeSpace *space);

            void setBoxSize(IAPIVector *v);
            IAPIVector *getBoxSize();
            /**
              * This method is not implemented.
              */
            double volume();
            virtual void nearestImage(IAPIVectorMutable *v) = 0;
            virtual IAPIVector *centralImage(IAPIVector *v) = 0;
            /**
              * This method is not implemented.
              */
            void setBox(IAPIBox *box);
            /**
              * This method is not implemented.
              */
            IAPIBox *getBox();
            virtual IAPIVector *getEdgeVector(int d) = 0;
            IAPIVector *getCenter();
            virtual bool getPeriodicity(int d) = 0;
            /*
              * This method is not implemented.
              */
            IAPIBoundaryEventManager *getEventManager();

        protected:
            IAPIVectorMutable *mDimensions;
            IAPIVectorMutable *mCenter;
            IAPIVectorMutable *mEdgeVector;
            TowheeSpace *mSpace;
    };
}

#endif
