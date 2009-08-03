/*
 *  LammpsPairTable.h
 *  API Glue
 *
 */

#ifndef LAMMPS_PAIR_TABLE_WRAPPER_H
#define LAMMPS_PAIR_TABLE_WRAPPER_H

#include <vector>

#include "LammpsPair.h"

using namespace molesimAPI;

namespace lammpswrappers
{

    class LammpsPairTable : public LammpsPair {

        public:			
            LammpsPairTable(int n, int values,
                            char *filename, char *keyword);
            LammpsPairTable(int n, int values,
                            char *filename, char *keyword, double cutoff);
            LammpsPairTable(int n, int values, int style,
                            char *filename, char *keyword);
            LammpsPairTable(int n, int values, int style,
                            char *filename, char *keyword,
                            double cutoff);

            // API Compliance
            double energy(IAPIAtomList *);
            void setBox(IAPIBox *);

            // Non-API methods
            char *getLookup();
            virtual char*getConstructionString();
            static const int VALUES_INDEX;

            // Table style consts
            static const int LOOKUP;
            static const int LINEAR;
            static const int SPLINE;
            static const int BITMAP;

        private:
            void setLookup(char *filename, char *keyword);
            void setLookup(char *filename, char *keyword, double cutoff);
            int tableStyle;
            static const char* const BOND_NAME;
            static const int    NPARMS;
            static const int    NCUTOFF;
            char *lookup;

    };

}
#endif
