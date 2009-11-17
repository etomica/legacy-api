/*
 *  IndexManager.h
 *  API Glue
 *
 */

#ifndef TOWHEE_INDEX_MANAGER_H
#define TOWHEE_INDEX_MANAGER_H

namespace towheesnifferwrappers
{

    class IndexManager {

        public:

            IndexManager(int startsAt);

            int getNextIndex();

        private:
            int currentIndex;
    };
}
#endif
