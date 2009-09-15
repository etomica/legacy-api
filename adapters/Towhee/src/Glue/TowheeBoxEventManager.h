/*
 *  TowheeBoxEventManager.h
 *  API Glue
 *
 */


#ifndef TOWHEE_BOX_EVENT_MANAGER_WRAPPER_H
#define TOWHEE_BOX_EVENT_MANAGER_WRAPPER_H

#include "IAPIBoxEventManager.h"
#include "IAPIBoxListener.h"

using namespace molesimAPI;

namespace towheewrappers
{

    class TowheeBoxEventManager :
                                public virtual IAPIBoxEventManager {

        public:

            // API Compliance
            void addListener(IAPIBoxListener *newListener);
            void removeListener(IAPIBoxListener *listener);

    };
}
#endif
