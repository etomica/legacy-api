/*
 *  IAPIFunction.h
 *  API Glue
 *
 */

#ifndef API_IFUNCTION_WRAPPER_H
#define API_IFUNCTION_WRAPPER_H


namespace molesimAPI
{

    class IAPIFunction {

        public:			
            virtual double f(double) = 0;

    };
}
#endif
