/*
 *  IAPIRandom.h
 *  API Glue
 *
 */

#ifndef API_IRANDOM_WRAPPER_H
#define API_IRANDOM_WRAPPER_H


namespace molesimAPI
{

    class IAPIRandom {

        public:			
            virtual double nextDouble() = 0;
            virtual int nextInt(int) = 0;
            virtual double nextGaussian() = 0;

    };
}
#endif
