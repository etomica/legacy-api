/*
 *  ObjectManager.cpp
 *  API Glue
 *
 *
 */

#include "ObjectManager.h"


namespace glotzwrappers
{	

    /*
     * addMapping()
     */
    void ObjectManager::addMapping(int glotzillaIndex, void *obj) {

            objectHash.insert(std::pair<int, void *>(glotzillaIndex, obj));
    }

    /*
     * getMapping()
     */
    void *ObjectManager::getMapping(int glotzillaIndex) {
        return(objectHash.find(glotzillaIndex)->second);
    }

    /*
     * removeMapping()
     */
    void ObjectManager::removeMapping(int glotzillaIndex) {

        objectHash.erase(glotzillaIndex);
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
