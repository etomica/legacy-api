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
            /**
              * Stores the kind of bond and bond parameters for construction
              * of a native Lammps bond_style command.  The number of
              * cutoffs is set to 0.
              * @param n Number of bodies in the potential
              * @param nParms Number of parameters relevant to the bond
              * @param type The type of bond
              */
            LammpsPotential(int n, int nParms, const char *type);		
            /**
              * Stores the kind of bond and bond parameters for construction
              * of a native Lammps bond_style command.
              * @param n Number of bodies in the potential
              * @param nParms Number of parameters relevant to the bond
              * @param nc Number of cutoff parameters relevant to the bond
              * @param type The type of bond
              */
            LammpsPotential(int n, int nParms, int nC, const char *type);		

            // API Compliance
            double getRange() = 0;
            int nBody();
            void setBox(IAPIBox *) = 0;

            // Non-API methods
            /**
              * Set one of the bond's construction parameters (which can
              * be used in the native Lammps bond_coeff command).
              * @param index Index of the parameter in the constuction list.
              * @param val Value of the parameter.
              */
            void setParameter(int index, double val);
            /**
              * Get one of the bond's construction parameters (which can
              * be used in the native Lammps bond_coeff command).
              * @param index Index of the parameter in the constuction list.
              */
            double getParameter(int index);
            /**
              * @return Returns the number of construction paremeters for
              *         the bond.
              */
            int getParameterCount();
            /**
              * @return Returns the bond type for the bond.
              *         (which is used in the native Lammps bond_style
              *         command)
              */
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
