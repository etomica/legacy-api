/*
 *  LammpsSimulationAtomTypeIndexEvent.h
 *  API Glue
 *
 */

#ifndef LAMMPS_SIMULATIONATOMTYPEINDEXEVENT_WRAPPER_H
#define LAMMPS_SIMULATIONATOMTYPEINDEXEVENT_WRAPPER_H

#include "IAPIAtomType.h"
#include "IAPISimulation.h"
#include "IAPISimulationAtomTypeIndexEvent.h"
#include "LammpsSimulationAtomTypeEvent.h"

using namespace molesimAPI;

namespace lammpswrappers
{

    class LammpsSimulationAtomTypeIndexEvent : public LammpsSimulationAtomTypeEvent,
                                        public virtual IAPISimulationAtomTypeIndexEvent {

        public:
            /**
              * @param sim Simulation pertaining to this event.
              * @param atomType Atom type pertaining to this event.
              * @param idx Index pertaining to this event.
              */
            LammpsSimulationAtomTypeIndexEvent(IAPISimulation *sim, IAPIAtomType *atomType, int idx);

            int getIndex();

        protected:
            int mIndex;

    };
}
#endif
