/*
 *  TowheeSimulationAtomTypeIndexEvent.h
 *  API Glue
 *
 */

#ifndef TOWHEE_SIMULATIONATOMTYPEINDEXEVENT_WRAPPER_H
#define TOWHEE_SIMULATIONATOMTYPEINDEXEVENT_WRAPPER_H

#include "IAPIAtomType.h"
#include "IAPISimulation.h"
#include "IAPISimulationAtomTypeIndexEvent.h"
#include "TowheeSimulationAtomTypeEvent.h"

using namespace molesimAPI;

namespace towheesnifferwrappers
{

    /**
      */
    class TowheeSimulationAtomTypeIndexEvent : public TowheeSimulationAtomTypeEvent,
                                        public virtual IAPISimulationAtomTypeIndexEvent {

        public:
            /**
              * @param sim Simulation pertaining to this event.
              * @param atomType Atom type pertaining to this event.
              * @param idx Index pertaining to this event.
              */
            TowheeSimulationAtomTypeIndexEvent(IAPISimulation *sim, IAPIAtomType *atomType, int idx);

            /**
              * @return Returns the index that this event is related to.
              */
            int getIndex();

        protected:
            int mIndex;

    };
}
#endif
