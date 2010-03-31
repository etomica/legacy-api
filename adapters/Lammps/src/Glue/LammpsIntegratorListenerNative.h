/*
 *  LammpsIntegratorListenerNative.h
 *  API Glue
 *
 */


#ifndef LAMMPS_INTEGERATOR_LISTENER_NATIVE_WRAPPER_H
#define LAMMPS_INTEGERATOR_LISTENER_NATIVE_WRAPPER_H

#include "jni.h"

#include "IAPIIntegratorListener.h"
#include "IAPIIntegratorEvent.h"

using namespace molesimAPI;

namespace lammpswrappers
{

    /**
      * An integrator listener that holds a java IIntegratorListener and calls
      * the IIntegratorListener's methods from its methods.  The integrator
      * event manager will notify an instance of this class upon an event and
      * this class will notify the java class instance it holds of the event.
      */
    class LammpsIntegratorListenerNative : public virtual IAPIIntegratorListener {

        public:
            /**
              * @param jenv The Java Native Interface (JNI) environment.
              * @param jobj The JNI object that holds the java integrator
              *             listener class instance.
              */
            LammpsIntegratorListenerNative(JNIEnv *jenv, jobject jobj);

            // API Compliance
            /**
              * The listener method called when the integrator is
              * initializing.  Passes the call to the java integrator
              * listener object held.
              * @param event Information relating to integrator event.
              */
            void integratorInitialized(IAPIIntegratorEvent *event);
            /**
              * The listener method called just prior to the integrator step.
              * Passes the call to the java integrator listener object held.
              * @param event Information relating to integrator event.
              */
            void integratorStepStarted(IAPIIntegratorEvent *event);
            /**
              * The listener method called directly after the integrator step.
              * Passes the call to the java integrator listener object held.
              * @param event Information relating to integrator event.
              */
            void integratorStepFinished(IAPIIntegratorEvent *event);

        private:
            jobject nativeObject;
            JNIEnv *getJavaEnv();
    };
}
#endif
