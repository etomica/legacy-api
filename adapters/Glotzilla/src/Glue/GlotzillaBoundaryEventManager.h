/*
 *  GlotzillaBoundaryEventManager.h
 *  API Glue
 *
 */

#ifndef GLOTZ_BOUNDARYEVENTMGR_WRAPPER_H
#define GLOTZ_BOUNDARYEVENTMGR_WRAPPER_H

#include <vector>

#include "IAPIBoundary.h"
#include "IAPIBoundaryEventManager.h"
#include "IAPIBoundaryListener.h"

using namespace molesimAPI;

namespace glotzwrappers
{

    /**
      * GlotzillaBoundaryEventManager fires boundary events to any listeners
      * registered to receive boundary events.  A listener is notified of any
      * boundary event whether the listener is interested in the event or not.
      * If the listener is not interested in the event, it can ignore the event.
      * The listener determines the kind of event by checking the type of
      * the event class.
      */
    class GlotzillaBoundaryEventManager : public virtual IAPIBoundaryEventManager {

        public:
            void addListener(IAPIBoundaryListener *listener);
            void removeListener(IAPIBoundaryListener *listener);

            // Non-API
            /**
              * This method is not implemented.
              */
            void inflate(IAPIBoundary *boundary);

        protected:
            std::vector<IAPIBoundaryListener *> listeners;
    };
}

#endif
