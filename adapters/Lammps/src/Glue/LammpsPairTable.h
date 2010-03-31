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
            /**
              * Creates a native Lammps pair_style of table.  Set the style
              * of the table to linear.  The optional cutoff value is not
              * specified.
              * @param n Number of bodies in the potential
              * @param values Lammps simulation pair_style N parameter.
              * @param filename Lammps simulation pair_coeff filename
              *                 parameter.
              * @param keyword Lammps simulation pair_coeff keyword
              *                parameter.
              */
            LammpsPairTable(int n, int values,
                            char *filename, char *keyword);
            /**
              * Creates a native Lammps pair_style of table.  Set the style
              * of the table to linear.
              * @param n Number of bodies in the potential
              * @param values Lammps simulation pair_style N parameter.
              * @param filename Lammps simulation pair_coeff filename
              *                 parameter.
              * @param keyword Lammps simulation pair_coeff keyword
              *                parameter.
              * @param cutoff Lammps simulation pair_coeff cutoff parameter.
              */
            LammpsPairTable(int n, int values,
                            char *filename, char *keyword, double cutoff);
            /**
              * Creates a native Lammps pair_style of table.
              * @param n Number of bodies in the potential
              * @param values Lammps simulation pair_style N parameter.
              * @param style Lammps simulation pair_style style parameter.
              *              Possible values :
              *                LOOKUP = 0;
              *                LINEAR = 1;
              *                SPLINE = 2;
              *                BITMAP = 3;
              * @param filename Lammps simulation pair_coeff filename
              *                 parameter.
              * @param keyword Lammps simulation pair_coeff keyword
              *                parameter.
              * @param cutoff Lammps simulation pair_coeff cutoff parameter.
              */
            LammpsPairTable(int n, int values, int style,
                            char *filename, char *keyword);
            /**
              * Creates a native Lammps pair_style of table.  The optional
              * cutoff value is not specified.
              * @param n Number of bodies in the potential
              * @param values Lammps simulation pair_style N parameter.
              * @param style Lammps simulation pair_style style parameter.
              *              Possible values :
              *                LOOKUP = 0;
              *                LINEAR = 1;
              *                SPLINE = 2;
              *                BITMAP = 3;
              * @param filename Lammps simulation pair_coeff filename
              *                 parameter.
              * @param keyword Lammps simulation pair_coeff keyword
              *                parameter.
              */
            LammpsPairTable(int n, int values, int style,
                            char *filename, char *keyword,
                            double cutoff);

            // API Compliance
            /**
              * This method is not implemented.
              */
            double energy(IAPIAtomList *);
            /**
              * This method is not implemented.
              */
            void setBox(IAPIBox *);

            // Non-API methods
            /**
              * @return Returns a string containing the
              *         filename/keyword/cutoff(optional) used in the native
              *         Lammps simulation pair_coeff command.
              */
            char *getLookup();
            /**
              * @return Returns a string containing the sytle/N used in the
              *         native Lammps simulation pair_style table command.
              */
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
