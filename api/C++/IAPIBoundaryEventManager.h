/*
 *  IAPIBoundaryEventManager.h
 *  API Glue
 *
 */

#ifndef API_IBOUNDARYEVENTMGR_WRAPPER_H
#define API_IBOUNDARYEVENTMGR_WRAPPER_H

#include "IAPIBoundaryListener.h"

namespace molesimAPI
{

    class IAPIBoundaryEventManager {

        public:			
            virtual void addListener(IAPIBoundaryListener *) = 0;
            virtual void removeListener(IAPIBoundaryListener *) = 0;

    };
}
#endif
