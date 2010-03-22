/*
 *  IAPIBoxEventManager.h
 *  API Glue
 *
 */

#ifndef API_IBOXEVENTMGR_WRAPPER_H
#define API_IBOXEVENTMGR_WRAPPER_H

//#include "IAPIBoxListener.h"

namespace molesimAPI
{

    class IAPIBoxListener;

    /**
      * IAPIBoxEventManager fires box events to any listeners
      * registered to receive box events.  A listener is notified of any box
      * event whether the listener is interested in the event or not.  If
      * the listener is not interested in the event, it can ignore the event.
      */

    class IAPIBoxEventManager {

        public:
            /**
              * Register a box listener to receive box events.
              * @param listener Box listener to receive events.
              */
            virtual void addListener(IAPIBoxListener *) = 0;
            /**
              * Unregister a box listener from receiving box events.
              * @param listener Box listener to unregister.
              */
            virtual void removeListener(IAPIBoxListener *) = 0;

    };
}
#endif
