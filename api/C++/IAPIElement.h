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
            /**
              * @return Returns the mass of objects of this element type.
              */
            virtual double getMass() = 0;
            /**
              * @return Returns the reciprocal mass of objects of this
              *         element type (1.0 / mass).
              */
            virtual double rm() = 0;
            virtual char *getSymbol() = 0;
    };
}
#endif
