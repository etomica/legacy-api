/*
 *  GlotzillaIntegratorListener.h
 *  API Glue
 *
 */

#ifndef GLOTZ_INTEGRATOR_LISTENER_WRAPPER_H
#define GLOTZ_INTEGRATOR_LISTENER_WRAPPER_H

#include <glotzmd.h>

#include "IAPIIntegratorEvent.h"
#include "IAPIIntegratorListener.h"

using namespace molesimAPI;

namespace glotzwrappers
{

    /**
      * GlotzillaIntegratorListener is a class that listens for integrator
      * events.  It is a native Glotzilla listener
      * (glotzmd::SimulationModifier) and as such can be added directly to a
      * native Glotzilla simulation (glotzmd::Simulation).  The class holds
      * an instance of an API compliant class that may not be a native
      * Glotzilla listener and notifies it of an integrator event when
      * it itself is notified by the native Glotzilla simulation of an
      * integrator event.
      */
    class GlotzillaIntegratorListener : public glotzmd::SimulationModifier,
                                        public virtual IAPIIntegratorListener {

        public:
            /**
              * @param listener API compliant integrator listener to pass
              *                 along integrator event notification.
              */
            GlotzillaIntegratorListener(IAPIIntegratorListener *listener);

            // API Compliance
            void integratorInitialized(IAPIIntegratorEvent *event);
            void integratorStepStarted(IAPIIntegratorEvent *event);
            void integratorStepFinished(IAPIIntegratorEvent *event);
            /**
              * The method that the native Glotzilla simulation calls when
              * the native Glotzilla simulation pre move pre force
              * operations should run.  This method is notified each time
              * pre move pre force actions should run.
              */
            void ApplyPreMovePreForce();
            /**
              * The method that the native Glotzilla simulation calls when
              * the native Glotzilla simulation post move post force
              * operations should run.  This method is notified each time
              * post move post force actions should run.
              */
            void ApplyPostMovePostForce();

        private:
            IAPIIntegratorListener *mListener;
    };
}

#endif
