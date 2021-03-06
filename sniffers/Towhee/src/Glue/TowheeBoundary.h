
/*
 *  TowheeBoundary.h
 *  API Glue
 *
 */

#ifndef TOWHEE_BOUNDARY_WRAPPER_H
#define TOWHEE_BOUNDARY_WRAPPER_H

#include "IAPIBoundary.h"
#include "IAPIBoundaryEventManager.h"
#include "IAPIVector.h"
#include "IAPIVectorMutable.h"

#include "TowheeSpace.h"

using namespace molesimAPI;

namespace towheesnifferwrappers
{

    class TowheeBoundary : public virtual IAPIBoundary {

        public:

            TowheeBoundary(TowheeSpace *space, IAPIVector *size);

            void setBoxSize(IAPIVector *v);
            IAPIVector *getBoxSize();
            virtual double volume() = 0;
            virtual void nearestImage(IAPIVectorMutable *v) = 0;
            virtual IAPIVector *centralImage(IAPIVector *v) = 0;
            void setBox(IAPIBox *box);
            IAPIBox *getBox();
            virtual IAPIVector *getEdgeVector(int d) = 0;
            IAPIVector *getCenter();
            virtual bool getPeriodicity(int d) = 0;
            IAPIBoundaryEventManager *getEventManager();

        protected:
            IAPIVectorMutable *mDimensions;
            IAPIVectorMutable *mCenter;
            IAPIVectorMutable *mEdgeVector;
            IAPIBox *mBox;
            TowheeSpace *mSpace;
    };
}

#endif
