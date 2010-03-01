/*
 *  TowheeForceField.cpp
 *  API Glue
 *
 *
 */

#include "stdio.h"
#if defined(__MACH__) && defined(__APPLE__)
#include "stdlib.h"
#else
#include "malloc.h"
#endif
#include "string.h"

#include "TowheeForceField.h"

namespace towheewrappers
{

//
// NOTE : The forcefield should have a unique index for getting
//        and setting in towhee code
//

    TowheeForceField::TowheeForceField(char *file, char *name) {
        mFilename = (char *) malloc ((strlen(file) + 1) * sizeof(char));
        strcpy(mFilename, file);
        mName = (char *) malloc ((strlen(name) + 1) * sizeof(char));
        strcpy(mName, name);
    }

    /*
     * getForcefieldName()
     */
    char *TowheeForceField::getForcefieldName() {
        return mName;
    }

    /*
     * getFileName()
     */
    char *TowheeForceField::getFileName() {
        return mFilename;
    }

    /*
     * setup()
     */
    void TowheeForceField::setup() {

//        twh_rwforcefield_();

        // Stuff that comes after call in readclassical.F

    }

}
