/*
 *  TowheeBoxEvent.h
 *  API Glue
 *
 */

#ifndef TOWHEE_BOXEVENT_WRAPPER_H
#define TOWHEE_BOXEVENT_WRAPPER_H

#include "IAPIBox.h"
#include "IAPIBoxEvent.h"

using namespace molesimAPI;

namespace towheesnifferwrappers
{

    class TowheeBoxEvent : public virtual IAPIBoxEvent {

        public:
            TowheeBoxEvent(IAPIBox *box);
            IAPIBox *getBox();

        protected:
            IAPIBox *mBox;

    };
}
#endif
