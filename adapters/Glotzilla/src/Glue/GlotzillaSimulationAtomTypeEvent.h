/*
 *  GlotzillaSimulationAtomTypeEvent.h
 *  API Glue
 *
 */

#ifndef GLOTZ_SIMULATIONATOMTYPEEVENT_WRAPPER_H
#define GLOTZ_SIMULATIONATOMTYPEEVENT_WRAPPER_H

#include "IAPIAtomType.h"
#include "IAPISimulation.h"
#include "IAPISimulationAtomTypeEvent.h"
#include "GlotzillaSimulationEvent.h"

using namespace molesimAPI;

namespace glotzwrappers
{

    /**
      */
    class GlotzillaSimulationAtomTypeEvent : public GlotzillaSimulationEvent,
                                        public virtual IAPISimulationAtomTypeEvent {

        public:
            /**
              * @param sim Simulation pertaining to this event.
              * @param atomType Atom type pertaining to this event.
              */
            GlotzillaSimulationAtomTypeEvent(IAPISimulation *sim, IAPIAtomType *atomType);

            /**
              * @return Returns the atom type that this event is related to.
              */
            IAPIAtomType *getAtomType();

        protected:
            IAPIAtomType *mAtomType;

    };
}
#endif
