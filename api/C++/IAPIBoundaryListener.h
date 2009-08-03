/*
 *  IAPIBoundaryListener.h
 *  API Glue
 *
 */

#ifndef API_IBOUNDARYLISTENER_WRAPPER_H
#define API_IBOUNDARYLISTENER_WRAPPER_H

#include "IAPIBoundaryEvent.h"

namespace molesimAPI
{

    class IAPIBoundaryListener {

        public:			
            virtual void boundaryInflate(IAPIBoundaryEvent *e) = 0;

    };
}
#endif
