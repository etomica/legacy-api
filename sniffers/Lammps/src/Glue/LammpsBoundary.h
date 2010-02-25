
/*
 *  LammpsBoundary.h
 *  API Glue
 *
 */

#ifndef LAMMPS_BOUNDARY_WRAPPER_H
#define LAMMPS_BOUNDARY_WRAPPER_H

#include <string>
#include <vector>

#include "IAPIBoundary.h"
#include "IAPIBoundaryEventManager.h"
#include "IAPIVector.h"
#include "IAPIVectorMutable.h"
#include "LammpsSimulation.h"
#include "LammpsSpace.h"

using namespace molesimAPI;

namespace lammpssnifferwrappers
{

    class LammpsBoundary : public virtual IAPIBoundary {

        public:
            LammpsBoundary(LammpsSimulation *sim);

            // API Compliance
            IAPIVector *getBoxSize();
            void setBoxSize(IAPIVector *v);
            double volume();
            void nearestImage(IAPIVectorMutable *v);
            IAPIVector *centralImage(IAPIVector *v);
            void setBox(IAPIBox *box);
            IAPIBox *getBox();
            virtual IAPIVector *getEdgeVector(int d);
            IAPIVector *getCenter();
            virtual bool getPeriodicity(int d) = 0;
            IAPIBoundaryEventManager *getEventManager();

        protected:
            LammpsSimulation *mSim;
            IAPIVectorMutable *mVector;
            IAPIVectorMutable *mEdge;
            IAPIBox *mBox;
            IAPIBoundaryEventManager *mEventMgr;

        private:
            IAPIVector *mCenter;

    };
}

#endif
