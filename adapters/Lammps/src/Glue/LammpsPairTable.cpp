/*
 *  LammpsPairTable.cpp
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

#include "LammpsPairTable.h"

namespace lammpswrappers
{

    const char *const LammpsPairTable::BOND_NAME = "table";
    const int LammpsPairTable::VALUES_INDEX = 0;
    const int LammpsPairTable::LOOKUP = 0;
    const int LammpsPairTable::LINEAR = 1;
    const int LammpsPairTable::SPLINE = 2;
    const int LammpsPairTable::BITMAP = 3;
    const int LammpsPairTable::NPARMS = 1;
    const int LammpsPairTable::NCUTOFF = 0;

    const char STYLES[4][20] = { "lookup", "linear", "spline", "bitmap" };

    LammpsPairTable::LammpsPairTable(int n, int values,
                                     char *filename, char *keyword)
                                   : LammpsPair(n, NPARMS, NCUTOFF, BOND_NAME) {
        setParameter(VALUES_INDEX, values);
        tableStyle = LINEAR;
        setLookup(filename, keyword);
    }

    LammpsPairTable::LammpsPairTable(int n, int values, char *filename,
                                     char *keyword, double cutoff)
                                   : LammpsPair(n, NPARMS, NCUTOFF, BOND_NAME) {
        setParameter(VALUES_INDEX, values);
        tableStyle = LINEAR;
        setLookup(filename, keyword, cutoff);
    }

    LammpsPairTable::LammpsPairTable(int n, int values, int style,
                                     char *filename, char *keyword)
                                   : LammpsPair(n, NPARMS, NCUTOFF, BOND_NAME) {
        setParameter(VALUES_INDEX, values);
        tableStyle = style;
        setLookup(filename, keyword);
    }

    LammpsPairTable::LammpsPairTable(int n, int values, int style, char *filename,
                                     char *keyword, double cutoff)
                                   : LammpsPair(n, NPARMS, NCUTOFF, BOND_NAME) {
        setParameter(VALUES_INDEX, values);
        tableStyle = style;
        setLookup(filename, keyword, cutoff);
    }

    /*
     * setLookup()
     */
    void LammpsPairTable::setLookup(char *filename, char *keyword) {
        char temp[128];
        sprintf(temp,
                "%s %s",
                filename,
                keyword);
        lookup = (char *) malloc ((strlen(temp) + 1) * sizeof(char));
        strcpy(lookup, temp);
    }

    /*
     * setLookup()
     */
    void LammpsPairTable::setLookup(char *filename, char *keyword, double cutoff) {
        char temp[128];
        sprintf(temp,
                "%s %s %f",
                filename,
                keyword,
                cutoff);
        lookup = (char *) malloc ((strlen(temp) + 1) * sizeof(char));
        strcpy(lookup, temp);
    }

    /*
     * energy()
     */
    double LammpsPairTable::energy(IAPIAtomList *as) {
        printf("WARNING : LammpsPairTable::energy() is NOT implemented yet.\n");
    }

    /*
     * setBox()
     */
    void LammpsPairTable::setBox(IAPIBox *b) {
        printf("WARNING : LammpsPairTable::setBox() is NOT implemented yet.\n");
    }

    /*
     * getLookup()
     */
    char *LammpsPairTable::getLookup() {
        return lookup;
    }

    /*
     * getConstructionString()
     */
    char *LammpsPairTable::getConstructionString() {


        char temp[128];
        strcpy(temp, "\0");
        sprintf(temp, "%s %.0f ",
                STYLES[tableStyle],
                parameters[VALUES_INDEX]);

        char *construction;
        construction = (char *) malloc ((strlen(temp) + 1) * sizeof(char));
        strcpy(construction, temp);

        return construction;
    }

}

