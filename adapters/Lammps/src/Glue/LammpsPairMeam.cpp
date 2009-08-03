/*
 *  LammpsPairMeam.cpp
 *  API Glue
 *
 */

#include "stdio.h"
#include "string.h"
#include "jni.h"

#ifdef __MACOSX__
#include "stdlib.h"
#else
#include "malloc.h"
#endif

#include "LammpsPairMeam.h"

namespace lammpswrappers
{

    const char *const LammpsPairMeam::BOND_NAME = "meam";

    LammpsPairMeam::LammpsPairMeam(JNIEnv *javaEnv, int n, jstring jlibraryFile,
                                   jstring jelements, jstring jparmFile) :
                                                     LammpsPair(n, 0, BOND_NAME) {
printf("ERROR : LammpsPairMeam is not fully implemented.\n"); fflush(stdout);
        const char *tmpLibFile = javaEnv->GetStringUTFChars(jlibraryFile, 0);
        const char *tmpInputFile = javaEnv->GetStringUTFChars(jparmFile, 0);
        const char *tmpElements = javaEnv->GetStringUTFChars(jelements, 0);

        libraryFile = (char *) malloc((strlen(tmpLibFile) + 1) * sizeof(char));
        parmFile = (char *) malloc((strlen(tmpInputFile) + 1) * sizeof(char));
        elements = (char *) malloc((strlen(tmpElements) + 1) * sizeof(char));

        strcpy(libraryFile, tmpLibFile);
        strcpy(elements, tmpElements);
        strcpy(parmFile, tmpInputFile);

        javaEnv->ReleaseStringUTFChars(jlibraryFile, tmpLibFile);
        javaEnv->ReleaseStringUTFChars(jparmFile, tmpInputFile);
        javaEnv->ReleaseStringUTFChars(jelements, tmpElements);

    }

    /*
     * energy()
     */
    double LammpsPairMeam::energy(IAPIAtomList *as) {
        printf("WARNING : LammpsPairMeam::energy() is NOT implemented yet.\n");
    }

    /*
     * setBox()
     */
    void LammpsPairMeam::setBox(IAPIBox *b) {
        printf("WARNING : LammpsPairMeam::setBox() is NOT implemented yet.\n");
    }

    /*
     * getLibraryFile()
     */
    char *LammpsPairMeam::getLibraryFile() {
        return libraryFile;
    }

    /*
     * getElements()
     */
    char *LammpsPairMeam::getElements() {
        return elements;
    }

    /*
     * getParameterFile()
     */
    char *LammpsPairMeam::getParameterFile() {
        return parmFile;
    }

}

