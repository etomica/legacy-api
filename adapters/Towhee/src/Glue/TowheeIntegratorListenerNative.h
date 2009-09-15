/*
 *  TowheeIntegratorListenerNative.h
 *  API Glue
 *
 */


#ifndef TOWHEE_INTEGERATOR_LISTENER_NATIVE_WRAPPER_H
#define TOWHEE_INTEGERATOR_LISTENER_NATIVE_WRAPPER_H

#include "jni.h"

#include "IAPIIntegratorListener.h"
#include "IAPIIntegratorEvent.h"

using namespace molesimAPI;

namespace towheewrappers
{

    class TowheeIntegratorListenerNative : public virtual IAPIIntegratorListener {

        public:			
            TowheeIntegratorListenerNative(JNIEnv *jenv, jobject jobj);

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
