/*
 *  IAPIElement.h
 *  API Glue
 *
 */

#ifndef API_IELEMENT_WRAPPER_H
#define API_IELEMENT_WRAPPER_H

namespace molesimAPI
{


    class IAPIElement {

        public:
            virtual double getMass() = 0;
            virtual double rm() = 0;
            virtual char *getSymbol() = 0;
    };
}
#endif
