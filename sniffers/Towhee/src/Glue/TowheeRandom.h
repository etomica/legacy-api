/*
 *  TowheeRandom.h
 *  API Glue
 *
 */

#ifndef TOWHEE_RANDOM_WRAPPER_H
#define TOWHEE_RANDOM_WRAPPER_H

#include "IAPIRandom.h"

using namespace molesimAPI;

namespace towheesnifferwrappers
{

    class TowheeRandom : public virtual IAPIRandom {

        public:
            TowheeRandom(long seed);
            TowheeRandom(long seed, int luxLevel);

            double nextDouble();
            int nextInt(int maxInt);
            double nextGaussian();

    };
}
#endif
