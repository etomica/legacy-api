/*
 *  TowheeSimulationAtomTypeEvent.h
 *  API Glue
 *
 */

#ifndef TOWHEE_SIMULATIONATOMTYPEEVENT_WRAPPER_H
#define TOWHEE_SIMULATIONATOMTYPEEVENT_WRAPPER_H

#include "IAPIAtomType.h"
#include "IAPISimulation.h"
#include "IAPISimulationAtomTypeEvent.h"
#include "TowheeSimulationEvent.h"

using namespace molesimAPI;

namespace towheesnifferwrappers
{

    /**
      */
    class TowheeSimulationAtomTypeEvent : public TowheeSimulationEvent,
                                        public virtual IAPISimulationAtomTypeEvent {

        public:
            /**
              * @param sim Simulation pertaining to this event.
              * @param atomType Atom type pertaining to this event.
              */
            TowheeSimulationAtomTypeEvent(IAPISimulation *sim, IAPIAtomType *atomType);

            /**
              * @return Returns the atom type that this event is related to.
              */
            IAPIAtomType *getAtomType();

        protected:
            IAPIAtomType *mAtomType;

    };
}
#endif
