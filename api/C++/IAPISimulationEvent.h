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
            virtual IAPISimulation *getSimulation() = 0;
    };
}
#endif
