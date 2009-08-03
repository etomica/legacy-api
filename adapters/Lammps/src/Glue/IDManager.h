/*
 *  IDManager.h
 *  API Glue
 *
 */

#ifndef ID_MANAGER_H
#define ID_MANAGER_H

namespace lammpswrappers
{

    class IDManager {

        public:
            IDManager(char *name);
            char *getNextID();

        private:
            int count;
            char *prefix;
    };

}

#endif
