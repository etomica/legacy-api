/*
 *  IDManager.cpp
 *  API Glue
 *
 */

#include "IDManager.h"

#include "stdio.h"
#include "string.h"

#if defined(__MACH__) && defined(__APPLE__)
#include "stdlib.h"
#else
#include "malloc.h"
#endif

namespace lammpssnifferwrappers
{

    IDManager::IDManager(char *name) {
        prefix = (char *) malloc ((strlen(name) + 1) * sizeof(char));
        strcpy(prefix, name);
        count = 0;
    }

    /*
     * getNextID()
     */
    char *IDManager::getNextID() {
        count++;
        char idString[512];
        sprintf(idString, "%d", count);
        char *id = (char *) malloc((strlen(idString) +
                     strlen(prefix) + 2) * sizeof(char));
        sprintf(id, "%s_%s", prefix, idString);
        return(id);
    }
}
