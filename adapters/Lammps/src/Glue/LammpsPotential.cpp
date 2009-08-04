/*
 *  LammpsPotential.cpp
 *  API Glue
 *
 */

#include "stdio.h"
#include "string.h"

#if defined(__MACH__) && defined(__APPLE__)
#include "stdlib.h"
#else
#include "malloc.h"
#endif

#include "LammpsPotential.h"

namespace lammpswrappers
{

    LammpsPotential::LammpsPotential(int n, int nParms, const char *type) {
        nBdy = n;
        nParameters = nParms;
        nCutoffs = 0;
        parameters = (double *) malloc (nParms * sizeof(double));
        bondType = (char *) malloc ((strlen(type) + 1) * sizeof(char));
        strcpy(bondType, type);
    }

    LammpsPotential::LammpsPotential(int n, int nParms, int nC, const char *type) {
        nBdy = n;
        nParameters = nParms;
        nCutoffs = nC;
        parameters = (double *) malloc (nParameters * sizeof(double));
        bondType = (char *) malloc ((strlen(type) + 1) * sizeof(char));
        strcpy(bondType, type);
    }

    /*
     * nBody()
     */
    int LammpsPotential::nBody() {
        return nBdy;
    }

    /*
     * setParameter()
     */
    void LammpsPotential::setParameter(int index, double val) {
        if(index >= 0 && index < nParameters) {
            parameters[index] = val;
        }
    }

    /*
     * getParameter()
     */
    double LammpsPotential::getParameter(int index) {
        if(index >= 0 && index < nParameters) {
            return parameters[index];
        }
    }

    /*
     * getParameterCount()
     */
    int LammpsPotential::getParameterCount() {
        return nParameters;
    }

    /*
     * getBondType()
     */
    char *LammpsPotential::getBondType() {
        return bondType;
    }

    /*
     * getConstructionString()
     */
    char *LammpsPotential::getConstructionString() {
        char temp[128];
        strcpy(temp, "\0");
        for(int i = nParameters-nCutoffs; i < nParameters; i++) {
            sprintf(temp, "%f ", parameters[i]);
        }

        char *cutoff;
        cutoff = (char *) malloc ((strlen(temp) + 1) * sizeof(char));
        strcpy(cutoff, temp);

        return cutoff;
    }

}

