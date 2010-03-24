/*
 *  LammpsSimulationAtomTypeEvent.h
 *  API Glue
 *
 */

#ifndef LAMMPS_SIMULATIONATOMTYPEEVENT_WRAPPER_H
#define LAMMPS_SIMULATIONATOMTYPEEVENT_WRAPPER_H

#include "IAPIAtomType.h"
#include "IAPISimulation.h"
#include "IAPISimulationAtomTypeEvent.h"
#include "LammpsSimulationEvent.h"

using namespace molesimAPI;

namespace lammpswrappers
{

    /**
      */
    class LammpsSimulationAtomTypeEvent : public LammpsSimulationEvent,
                                        public virtual IAPISimulationAtomTypeEvent {

        public:
            /**
              * @param sim Simulation pertaining to this event.
              * @param atomType Atom type pertaining to this event.
              */
            LammpsSimulationAtomTypeEvent(IAPISimulation *sim, IAPIAtomType *atomType);

            IAPIAtomType *getAtomType();

        protected:
            IAPIAtomType *mAtomType;

    };
}
#endif
