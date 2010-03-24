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
            /**
              * @return Returns a pseudorandom double, uniformly distributed
              * between 0.0 (inclusive) and 1.0 (exclusive).
              */
            virtual double nextDouble() = 0;
            /**
             * @param Maximum value of the returned value
             * @return Returns a pseudorandom integer, uniformly distributed
             * between 0 (inclusive) and maxInt (exclusive).
             */
            virtual int nextInt(int) = 0;
            /**
              * @return Returns a pseudorandom double, Gaussian ("normally")
              * distributed value with mean 0.0 and standard deviation 1.0.
              */
            virtual double nextGaussian() = 0;

    };
}
#endif
