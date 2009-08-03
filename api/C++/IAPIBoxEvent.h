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

    class IAPIBoxEvent {

        public:			
            virtual IAPIBox *getBox() = 0;
    };
}
#endif
