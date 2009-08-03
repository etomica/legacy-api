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

    class LammpsPairMeam : public LammpsPair {

        public:			
            LammpsPairMeam(JNIEnv *javaEnv, int n, jstring jlibraryFile, jstring jelements, jstring jparmFile);		

            // API Compliance
            double energy(IAPIAtomList *);
            void setBox(IAPIBox *);

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
