/*
 *  ObjectManager.cpp
 *  API Glue
 *
 */

#include "ObjectManager.h"

namespace lammpswrappers
{	

    /*
     * addMapping()
     */
    void ObjectManager::addMapping(int lammpsIndex, void *obj) {

            objectHash.insert(std::pair<int, void *>(lammpsIndex, obj));
    }

    /*
     * getMapping()
     */
    void *ObjectManager::getMapping(int lammpsIndex) {

        return(objectHash.find(lammpsIndex)->second);
    }

    /*
     * removeMapping()
     */
    void ObjectManager::removeMapping(int lammpsIndex) {

        objectHash.erase(lammpsIndex);
    }

    /*
     * printMappings()
     */

    void ObjectManager::printMappings() {

        std::map<int, void *>::iterator it;

        for(it = objectHash.begin(); it != objectHash.end(); it++) {
            printf("Key : %d   Obj Address : %p\n", it->first, it->second);
        }
    }


}
