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
            /**
              * Method called when the boundary event manager is propogating
              * a boundary inflate event.
              * @param e
              */ 
            virtual void boundaryInflate(IAPIBoundaryEvent *e) = 0;

    };
}
#endif
