/*
 *  GlotzillaSimulationAtomTypeIndexEvent.h
 *  API Glue
 *
 */

#ifndef GLOTZ_SIMULATIONATOMTYPEINDEXEVENT_WRAPPER_H
#define GLOTZ_SIMULATIONATOMTYPEINDEXEVENT_WRAPPER_H

#include "IAPIAtomType.h"
#include "IAPISimulation.h"
#include "IAPISimulationAtomTypeIndexEvent.h"
#include "GlotzillaSimulationAtomTypeEvent.h"

using namespace molesimAPI;

namespace glotzwrappers
{

    /**
      */
    class GlotzillaSimulationAtomTypeIndexEvent : public GlotzillaSimulationAtomTypeEvent,
                                        public virtual IAPISimulationAtomTypeIndexEvent {

        public:
            /**
              * @param sim Simulation pertaining to this event.
              * @param atomType Atom type pertaining to this event.
              * @param idx Index pertaining to this event.
              */
            GlotzillaSimulationAtomTypeIndexEvent(IAPISimulation *sim, IAPIAtomType *atomType, int idx);

            int getIndex();

        protected:
            int mIndex;

    };
}
#endif
