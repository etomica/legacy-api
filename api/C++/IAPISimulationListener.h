/*
 *  IAPISimulationListener.h
 *  API Glue
 *
 */

#ifndef API_ISIMULATIONLISTENER_WRAPPER_H
#define API_ISIMULATIONLISTENER_WRAPPER_H

#include "IAPISimulationBoxEvent.h"
#include "IAPISimulationSpeciesEvent.h"
#include "IAPISimulationSpeciesIndexEvent.h"
#include "IAPISimulationIndexEvent.h"
#include "IAPISimulationAtomTypeIndexEvent.h"

namespace molesimAPI
{

    class IAPISimulationListener {

        public:			
            virtual void simulationBoxAdded(IAPISimulationBoxEvent *e) = 0;
            virtual void simulationBoxRemoved(IAPISimulationBoxEvent *e) = 0;
            virtual void simulationSpeciesAdded(IAPISimulationSpeciesEvent *e) = 0;
            virtual void simulationSpeciesRemoved(IAPISimulationSpeciesEvent *e) = 0;
            virtual void simulationSpeciesIndexChanged(IAPISimulationSpeciesIndexEvent *e) = 0;
            virtual void simulationSpeciesMaxIndexChanged(IAPISimulationIndexEvent *e) = 0;
            virtual void simulationAtomTypeIndexChanged(IAPISimulationAtomTypeIndexEvent *e) = 0;
            virtual void simulationAtomTypeMaxIndexChanged(IAPISimulationIndexEvent *e) = 0;

    };
}
#endif
