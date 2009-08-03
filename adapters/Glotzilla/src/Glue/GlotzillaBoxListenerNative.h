/*
 *  GlotzillaBoxListenerNative.h
 *  API Glue
 *
 */

#ifndef GLOTZ_NATIVEBOXLISTENER_WRAPPER_H
#define GLOTZ_NATIVEBOXLISTENER_WRAPPER_H

#include <glotzmd.h>

#include "jni.h"

#include "IAPIBoxEvent.h"
#include "IAPIBoxListener.h"

using namespace molesimAPI;

namespace glotzwrappers
{

    /**
      */
    class GlotzillaBoxListenerNative : public virtual IAPIBoxListener {

        public:
            /**
              */
            GlotzillaBoxListenerNative(JNIEnv *jenv, jobject jobj);

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
