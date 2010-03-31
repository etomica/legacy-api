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

    /**
      * ObjectManager stores an index (hopefully unique) and an object
      * pointer as a pair.  An object can be retrieved using its index.
      *
      */
    class ObjectManager {

        public:
            /**
              * Holds an association between the index (which should be
              * unique, although the method does not check) and an
              * object pointer (any object type).
              * @param lammpsIndex The index to associate with the
              *                    given index.
              * @param obj Object associated with the unique index
              */
            void addMapping(int lammpsIndex, void *obj);
            /**
              * @param lammpsIndex The index associated with the
              *                     object to retrieve.
              * @return Returns the object associated with the given
              *         index.
              */
            void *getMapping(int lammpsIndex);
            /**
              * Removes the association entry held in this class between
              * the index and an object pointer (any object type).
              * @param lammpsIndex The index contained in the
              *                    mapping to delete.
              */
            void removeMapping(int lammpsIndex);
            /**
              * Print (to screen) the index/pointer associations this
              * class is holding.
              */
            void printMappings();

        private:
          std::map<int, void *> objectHash;
    };

}

#endif
