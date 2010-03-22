
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
#include "IAPISimulation.h"
#include "IAPIVector.h"
#include "IAPIVectorMutable.h"
#include "LammpsSimulation.h"

using namespace molesimAPI;

namespace lammpswrappers
{

    class LammpsBoundary : public virtual IAPIBoundary {

        public:
            /**
              * Constructor for TowheeBoundary.  TowheeBoundary is
              * a purely virtual class and the constructor is only called
              * from its subclasses.
              * @param sim The simulation that holds the boundary.
              */
            LammpsBoundary(IAPISimulation *sim);

            // API Compliance
            /**
              * Determines the box size of the boundary by reaching into the
              * native Lammps simulation.
              * @return Returns the length of the boundary in each dimension
              *         that the boundary would be inscribed in.
              */
            IAPIVector *getBoxSize();
            void setBoxSize(IAPIVector *v);
            /**
              * Determines the box dimensions of the boundary by reaching
              * into the native Lammps simulation.
              * @return Returns the volume enclosed by the boundary.
              *         Assumes the boundary is rectangular.
              */
            double volume();
            /**
              * This method is not implemented.
              */
            void nearestImage(IAPIVectorMutable *v);
            /**
              * This method is not implemented.
              */
            IAPIVector *centralImage(IAPIVector *v);
            void setBox(IAPIBox *box);
            IAPIBox *getBox();
            virtual IAPIVector *getEdgeVector(int d) = 0;
            IAPIVector *getCenter();
            virtual bool getPeriodicity(int d) = 0;
            IAPIBoundaryEventManager *getEventManager();

            // Non-API methods
            virtual void lammpsSetup() = 0;

        protected:
            LammpsSimulation *mSim;
            IAPIVectorMutable *mVector;
            IAPIVector *mCenter;
            IAPIBox *mBox;
            IAPIBoundaryEventManager *mEventMgr;
    };
}

#endif
