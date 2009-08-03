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

    class IAPIBoxEventManager {

        public:			
            virtual void addListener(IAPIBoxListener *) = 0;
            virtual void removeListener(IAPIBoxListener *) = 0;

    };
}
#endif
