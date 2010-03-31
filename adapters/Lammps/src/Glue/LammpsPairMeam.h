/*
 *  LammpsPairMeam.h
 *  API Glue
 *
 */

#ifndef LAMMPS_PAIR_MEAM_WRAPPER_H
#define LAMMPS_PAIR_MEAM_WRAPPER_H

#include "jni.h"

#include "LammpsPair.h"

using namespace molesimAPI;

namespace lammpswrappers
{

    /**
      * This class is not functional and an instance should not be
      * created.
      */
    class LammpsPairMeam : public LammpsPair {

        public:
            /**
              * This class is not functional and an instance should not be
              * created.
              */
            LammpsPairMeam(JNIEnv *javaEnv, int n, jstring jlibraryFile, jstring jelements, jstring jparmFile);		

            // API Compliance
            /**
              * This method is not implemented.
              */
            double energy(IAPIAtomList *as);
            /**
              * This method is not implemented.
              */
            void setBox(IAPIBox *b);

            // Non-API methods
            char *getLibraryFile();
            char *getElements();
            char *getParameterFile();

        private:
            static const char* const BOND_NAME;
            char *libraryFile;
            char *elements;
            char *parmFile;
    };

}
#endif
