/*
 *  IAPIBoxEvent.h
 *  API Glue
 *
 */

#ifndef API_IBOXEVENT_WRAPPER_H
#define API_IBOXEVENT_WRAPPER_H

namespace molesimAPI
{

    class IAPIBox;

    /**
      * IAPIBoxEvent is an event superclass for events that are
      * related to some event within a box.
      */
    class IAPIBoxEvent {

        public:
            /**
              * @return Returns the box that this event is related to.
              */
            virtual IAPIBox *getBox() = 0;
    };
}
#endif
