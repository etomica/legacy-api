/*
 *  ObjectManager.h
 *  API Glue
 *
 */

#ifndef OBJECT_MANAGER_H
#define OBJECT_MANAGER_H

#include <map>

namespace lammpswrappers
{

    class ObjectManager {

        public:
            void addMapping(int lammpsIndex, void *obj);
            void *getMapping(int lammpsIndex);
            void removeMapping(int lammpsIndex);
            void printMappings();

        private:
          std::map<int, void *> objectHash;
    };

}

#endif
