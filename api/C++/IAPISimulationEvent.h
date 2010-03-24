/*
 *  IAPISimulationEvent.h
 *  API Glue
 *
 */

#ifndef API_ISIMULATIONEVENT_WRAPPER_H
#define API_ISIMULATIONEVENT_WRAPPER_H

namespace molesimAPI
{

    class IAPISimulation;

    class IAPISimulationEvent {

        public:
            /**
              * @return Returns the simulation that this event is related to.
              */
            virtual IAPISimulation *getSimulation() = 0;
    };
}
#endif
