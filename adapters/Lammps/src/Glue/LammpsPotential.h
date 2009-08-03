/*
 *  LammpsPotential.h
 *  API Glue
 *
 */

#ifndef LAMMPS_POTENTIAL_WRAPPER_H
#define LAMMPS_POTENTIAL_WRAPPER_H


#include "IAPIPotential.h"

using namespace molesimAPI;

namespace lammpswrappers
{

    class LammpsPotential : public virtual IAPIPotential {

        public:			
            LammpsPotential(int n, int nParms, const char *type);		
            LammpsPotential(int n, int nParms, int nC, const char *type);		

            // API Compliance
            double getRange() = 0;
            int nBody();
            void setBox(IAPIBox *) = 0;

            // Non-API methods
            void setParameter(int index, double val);
            double getParameter(int index);
            int getParameterCount();
            char *getBondType();
            virtual char *getConstructionString();

        protected:
            int    nBdy;
            double *parameters;

        private:
            int    nParameters;
            int    nCutoffs;
            char   *bondType;

    };
}
#endif
