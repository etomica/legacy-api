/*
 *  TowheePotentialLennardJones.h
 *  API Glue
 *
 *
 */

#ifndef TOWHEE_POTENTIAL_LENNARD_JONES_WRAPPER_H
#define TOWHEE_POTENTIAL_LENNARD_JONES_WRAPPER_H

#include "IAPIAtomList.h"

#include "TowheePotential.h"

using namespace molesimAPI;

namespace towheewrappers
{

    class TowheePotentialLennardJones : public TowheePotential {

        public:

            TowheePotentialLennardJones();

            // API Compliance
            virtual double energy(IAPIAtomList *);

            // Non-API Compliance
            void setup();
            void setClassicalMixRule(int mixRule);

            static const int LORENTZ_BERTHELOT;
            static const int GEOMETRIC;
            static const int EXPLICIT;
            static const int SHUKLA;
            //static const int LB_PLUS_MANUAL;

        private:
            int mMixRule;
            bool mLShift;
            bool mTailc;
            double mRMin;
            double mRCut;
            double mRCutin;

    };
}
#endif
