/*
 *  TowheeAtomPositionDefinitionNative.h
 *  API Glue
 *
 */

#ifndef TOWHEE_NATIVEATOMPOSDEF_WRAPPER_H
#define TOWHEE_NATIVEATOMPOSDEF_WRAPPER_H

#include "jni.h"

#include "TowheeInterfaceAtomPositionDefinition.h"
#include "IAPIMolecule.h"
#include "IAPIVector.h"

#include "TowheeAtomPositionDefinition.h"
#include "TowheeSpace.h"

using namespace molesimAPI;

namespace towheewrappers
{

    /**
      * The class holds a java IAtomPositionDefinition instance and when
      * the position method is called, calls the java IAtomPositionDefinition
      * which holds the algorithm to determine the position of the molecule.
      *
      * This class is only used in simulations being written in Java.
      */
    class TowheeAtomPositionDefinitionNative :
                                  public TowheeAtomPositionDefinition,
                                  public virtual TowheeInterfaceAtomPositionDefinition {

        public:
            /**
              *
              * @param jenv The Java Native Interface (JNI) environment.
              * @param jobj The JNI object that holds the java atom positin
              *             definitin class instance.
              * @param sim Simulation that the atom position definition is a
              *            part of.
              */
            TowheeAtomPositionDefinitionNative(JNIEnv *jenv,
                                               jobject jobj,
                                               TowheeSpace *space);

            // API Compliance
            /**
              * WARNING : This method should not be called.
              * @return Returns NULL.
              */
            IAPIVector *position(IAPIMolecule *atom);

            // Non-API Methods
            /**
              * Calls the position method on the java instance of the
              * IAtomPositionDefinition that this class holds and passes
              * the java instance of IMolecule that was passed in.  The
              * java object should determine the position of the molecule.
              * @param atom Is a java object which implements IMolecule.
              * @return Returns the position of the molecule as determined.
              */
            IAPIVector *position(jobject atom);

        private:
            jobject nativeObject;
            TowheeSpace *mSpace;
    };
}
#endif
