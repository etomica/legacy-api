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
            /**
              * This method is not implemented.
              */
            void addListener(IAPIBoxListener *newListener);
            /**
              * This method is not implemented.
              */
            void removeListener(IAPIBoxListener *listener);

    };
}
#endif
