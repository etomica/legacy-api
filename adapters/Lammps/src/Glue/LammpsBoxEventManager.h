/*
 *  LammpsBoxEventManager.h
 *  API Glue
 *
 */

#ifndef LAMMPS_BOXEVENTMGR_WRAPPER_H
#define LAMMPS_BOXEVENTMGR_WRAPPER_H

#include "IAPIBoxEventManager.h"
#include "IAPIBoxListener.h"

using namespace molesimAPI;

namespace lammpswrappers
{

    class LammpsBoxEventManager : public virtual IAPIBoxEventManager {

        public:
            /**
              * This method is not implemented.
              */
            void addListener(IAPIBoxListener *listener);
            /**
              * This method is not implemented.
              */
            void removeListener(IAPIBoxListener *listener);


    };
}

#endif
