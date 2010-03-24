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
            /**
              * Method called by simulation event manager when a box is
              * added to the simulation.
              * @param e Simulation event containing event information.
              */
            virtual void simulationBoxAdded(IAPISimulationBoxEvent *e) = 0;
            /**
              * Method called by simulation event manager when a box is
              * removed to the simulation.
              * @param e Simulation event containing event information.
              */
            virtual void simulationBoxRemoved(IAPISimulationBoxEvent *e) = 0;
            /**
              * Method called by simulation event manager when a species is
              * added to the simulation.
              * @param e Simulation event containing event information.
              */
            virtual void simulationSpeciesAdded(IAPISimulationSpeciesEvent *e) = 0;
            /**
              * Method called by simulation event manager when a species is
              * removed to the simulation.
              * @param e Simulation event containing event information.
              */
            virtual void simulationSpeciesRemoved(IAPISimulationSpeciesEvent *e) = 0;
            /**
              * Method called by simulation event manager when a specie's
              * index is changed.
              * @param e Simulation event containing event information.
              */
            virtual void simulationSpeciesIndexChanged(IAPISimulationSpeciesIndexEvent *e) = 0;
            virtual void simulationSpeciesMaxIndexChanged(IAPISimulationIndexEvent *e) = 0;
            /**
              * Method called by simulation event manager when an atom
              * type's index is changed.
              * @param e Simulation event containing event information.
              */
            virtual void simulationAtomTypeIndexChanged(IAPISimulationAtomTypeIndexEvent *e) = 0;
            virtual void simulationAtomTypeMaxIndexChanged(IAPISimulationIndexEvent *e) = 0;

    };
}
#endif
