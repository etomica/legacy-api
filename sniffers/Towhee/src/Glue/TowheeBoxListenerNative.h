/*
 *  TowheeBoxListenerNative.h
 *  API Glue
 *
 */

#ifndef TOWHEE_NATIVEBOXLISTENER_WRAPPER_H
#define TOWHEE_NATIVEBOXLISTENER_WRAPPER_H

#include "jni.h"

#include "IAPIBoxEvent.h"
#include "IAPIBoxAtomEvent.h"
#include "IAPIBoxAtomIndexEvent.h"
#include "IAPIBoxIndexEvent.h"
#include "IAPIBoxMoleculeEvent.h"
#include "IAPIBoxMoleculeIndexEvent.h"
#include "IAPIBoxMoleculeCountEvent.h"
#include "IAPIBoxListener.h"

using namespace molesimAPI;

namespace towheesnifferwrappers
{

    /**
      */
    class TowheeBoxListenerNative : public virtual IAPIBoxListener {

        public:
            /**
              */
            TowheeBoxListenerNative(JNIEnv *jenv, jobject jobj);

            // API Compliance
            /**
              */
            void boxAtomAdded(IAPIBoxAtomEvent *e);
            void boxAtomRemoved(IAPIBoxAtomEvent *e);
            void boxMoleculeAdded(IAPIBoxMoleculeEvent *e);
            void boxMoleculeRemoved(IAPIBoxMoleculeEvent *e);
            void boxGlobalAtomLeafIndexChanged(IAPIBoxIndexEvent *e);
            void boxGlobalAtomIndexChanged(IAPIBoxIndexEvent *e);
            void boxAtomLeafIndexChanged(IAPIBoxAtomIndexEvent *e);
            void boxMoleculeIndexChanged(IAPIBoxMoleculeIndexEvent *e);
            void boxNumberMolecules(IAPIBoxMoleculeCountEvent *e);

        private:
            jobject nativeObject;
            JNIEnv *getJavaEnv();

    };
}

#endif
