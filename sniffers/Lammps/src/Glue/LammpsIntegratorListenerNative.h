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

namespace lammpssnifferwrappers
{

    class LammpsIntegratorListenerNative : public virtual IAPIIntegratorListener {

        public:			
            LammpsIntegratorListenerNative(JNIEnv *jenv, jobject jobj);

            // API Compliance
            void integratorInitialized(IAPIIntegratorEvent *event);
            void integratorStepStarted(IAPIIntegratorEvent *event);
            void integratorStepFinished(IAPIIntegratorEvent *event);

        private:
            jobject nativeObject;
            JNIEnv *getJavaEnv();
    };
}
#endif
