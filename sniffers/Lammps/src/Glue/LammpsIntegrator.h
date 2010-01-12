/*
 *  LammpsIntegrator.h
 *  API Glue
 *
 */


#ifndef LAMMPS_INTEGERATOR_WRAPPER_H
#define LAMMPS_INTEGERATOR_WRAPPER_H

#include "IAPIBox.h"
#include "IAPIIntegrator.h"
#include "IAPIIntegratorEventManager.h"
//#include "LammpsMomentum.h"
//#include "LammpsNVE.h"
//#include "LammpsNVT.h"
//#include "LammpsNPT.h"
//#include "LammpsNPH.h"
#include "LammpsSimulation.h"

using namespace molesimAPI;
using namespace LAMMPS_NS;

namespace lammpssnifferwrappers
{

    class LammpsIntegrator : public virtual IAPIIntegrator {

        public:			
            LammpsIntegrator(LammpsSimulation *sim);

            // API Compliance
            void doStep();		
            long long getStepCount();		
            void reset();
            void resetStepCount();
            IAPIIntegratorEventManager *getEventManager();

            // Non-API methods
/*
            void setNVE(LammpsNVE *nve); // ARG LIST COMPELTE
            void setNVT(LammpsNVT *nvt); // ARG LIST COMPELTE
            void setNPT(LammpsNPT *npt); // ARG LIST NOT COMPLETE
            void setNPH(LammpsNPH *nph); // ARG LIST NOT COMPELTE
*/

            void setTimestep(double ts);
            void doSteps(int nSteps);


        protected:
            LammpsSimulation *mSimulation;

        private:
            long long stepCount;
            IAPIIntegratorEventManager *mEventManager;

            // Fix type parameters
/*
            static const int NONE;
            static const int NVE;
            static const int NVT;
            static const int NPT;
            static const int NPH;
            int fixType;

            LammpsNVE *fixNVE;
            LammpsNVT *fixNVT;
            LammpsNPT *fixNPT;
            LammpsNPH *fixNPH;
*/

    };
}
#endif
