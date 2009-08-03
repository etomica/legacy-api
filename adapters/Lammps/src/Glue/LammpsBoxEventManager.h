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
            void addListener(IAPIBoxListener *listener);
            void removeListener(IAPIBoxListener *listener);

        protected:

    };
}

#endif
