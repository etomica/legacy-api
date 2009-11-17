/*
 *  TowheeIntegratorListenerNative.h
 *  API Glue
 *
 */


#ifndef TOWHEE_INTEGERATOR_LISTENER_NATIVE_WRAPPER_H
#define TOWHEE_INTEGERATOR_LISTENER_NATIVE_WRAPPER_H

#include "jni.h"

#include "IAPIIntegratorEvent.h"
#include "IAPIIntegratorListener.h"

using namespace molesimAPI;

namespace towheesnifferwrappers
{
    /**
      * An integrator listener that holds a java IIntegratorListener and calls
      * the IIntegratorListener's methods from its methods.
      */
    class TowheeIntegratorListenerNative :
                                public virtual IAPIIntegratorListener {

        public:
            /**
              *
              */			
            TowheeIntegratorListenerNative(JNIEnv *jenv, jobject jobj);

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

        private:
            jobject nativeObject;
            JNIEnv *attachThread();
            void detachThread();


    };
}
#endif
