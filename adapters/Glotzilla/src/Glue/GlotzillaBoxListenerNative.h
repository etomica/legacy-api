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
      * The class holds a java object which implements IBoxListener.  An
      * instance of the class can be added to a box event manager.  When
      * the box event manager dispatches events, an instance of this class
      * will be notified, which in turn notifies the java object that it
      * is holding of the box event.
      */
    class GlotzillaBoxListenerNative : public virtual IAPIBoxListener {

        public:
            /**
              * Create the box listener.
              * @param jenv The java native environment.
              * @param obj The java object, which MUST be an instance of a
              *            class that implements the java interface
              *            IBoxListener.
              */
            GlotzillaBoxListenerNative(JNIEnv *jenv, jobject jobj);

            // API Compliance
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
