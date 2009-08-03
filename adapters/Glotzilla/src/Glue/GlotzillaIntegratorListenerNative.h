/*
 *  GlotzillaIntegratorListenerNative.h
 *  API Glue
 *
 */


#ifndef GLOTZ_INTEGERATOR_LISTENER_NATIVE_WRAPPER_H
#define GLOTZ_INTEGERATOR_LISTENER_NATIVE_WRAPPER_H

#include "jni.h"

#include <glotzmd.h>

#include "IAPIIntegratorEvent.h"
#include "IAPIIntegratorListener.h"

using namespace molesimAPI;

namespace glotzwrappers
{
    /**
      * An integrator listener that holds a java IIntegratorListener and calls
      * the IIntegratorListener's methods from its methods.
      */
    class GlotzillaIntegratorListenerNative : public glotzmd::SimulationModifier,
                                public virtual IAPIIntegratorListener {

        public:
            /**
              *
              */			
            GlotzillaIntegratorListenerNative(JNIEnv *jenv, jobject jobj);

            /**
              * The listener method called when the integrator is
              * initializeing.
              * @param event Information relating to integrator event.
              */
            void integratorInitialized(IAPIIntegratorEvent *event);
            /**
              * The listener method called just prior to the integrator step.
              * @param event Information relating to integrator event.
              */
            void integratorStepStarted(IAPIIntegratorEvent *event);
            /**
              * The listener method called directly after the integrator step.
              * @param event Information relating to integrator event.
              */
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
            jobject nativeObject;
            JNIEnv *attachThread();
            void detachThread();


    };
}
#endif
