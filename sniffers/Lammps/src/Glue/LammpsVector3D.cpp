/*
 *  LammpsVector3D.cpp
 *  API Glue
 *
 */

#include <math.h>
#include "stdio.h"

#if defined(__MACH__) && defined(__APPLE__)
#include "stdlib.h"
#else
#include "malloc.h"
#endif

#include "LammpsVector3D.h"

namespace lammpssnifferwrappers
{

    LammpsVector3D::LammpsVector3D() {
        D = 3;
        pos = (double ***) malloc (1 * sizeof(double **));
        pos[0] = (double **) malloc (1 * sizeof(double *));
        pos[0][0] = (double *) malloc (D * sizeof(double));
        for(int i = 0; i < D; i++)
            pos[0][0][i] = 0.0;
        mIndex = 0;
        memoryOwn = true;
    }

    LammpsVector3D::LammpsVector3D(double ***v) {
        pos = v;
        D = 3;
        mIndex = 0;
        memoryOwn = false;
    }

    LammpsVector3D::LammpsVector3D(double ***v, int idx) {
        pos = v;
        D = 3;
        mIndex = idx;
        memoryOwn = false;
    }

    /*
     * getD
     */
    int LammpsVector3D::getD() {
        return D;
    }

    /*
     * assignTo
     */
    void LammpsVector3D::assignTo(double values[]) {
/*
    printf("------------------- ASSIGN TO ----------------------------\n");
    printf("data address : %x  contains : %x\n", &pos, pos);
    printf("  data address[%d] : %x  contains : %x\n", mIndex,
           &pos[mIndex], pos[mIndex]);
        for(int j = 0; j < 3; j++) {
            printf("    data address[%d][%d] : %x  contains : %f\n", mIndex, j,
                   &pos[mIndex][j], pos[mIndex][j]);
        }
    printf("------------------ END ASSIGN TO --------------------------\n"); fflush(stdout);
*/
        values[0] = pos[0][mIndex][0];
        values[1] = pos[0][mIndex][1];
        values[2] = pos[0][mIndex][2];
    }

    /*
     * equals
     */
    bool LammpsVector3D::equals(IAPIVector *v) {
        bool eq = false;

        if(v->getX(0) == pos[0][mIndex][0] &&
           v->getX(1) == pos[0][mIndex][1] &&
           v->getX(2) == pos[0][mIndex][2]) {
            eq = true;
        }

        return eq;
    }

    /*
     * x
     */
    double LammpsVector3D::getX(int index) {
        double value = 0.0;
        if(index == 0) {
            value = pos[0][mIndex][0];
        }
        else if(index == 1) {
            value = pos[0][mIndex][1];
        }
        else {
            value = pos[0][mIndex][2];
        }
        return value;
    }

    /*
     * setX
     */
    void LammpsVector3D::setX(int index, double value) {
        if(index == 0) {
            pos[0][mIndex][0] = value;
        }
        else if(index == 1) {
            pos[0][mIndex][1] = value;
        }
        else {
            pos[0][mIndex][2] = value;
        }
    }

    /*
     * E
     */
    void LammpsVector3D::E(IAPIVector *v) {
        pos[0][mIndex][0] = v->getX(0);
        pos[0][mIndex][1] = v->getX(1);
        pos[0][mIndex][2] = v->getX(2);
    }

    /*
     * E
     */
    void LammpsVector3D::E(double d) {
        pos[0][mIndex][0] = d;
        pos[0][mIndex][1] = d;
        pos[0][mIndex][2] = d;
    }

    /*
     * E
     */
    void LammpsVector3D::E(double d[]) {
        pos[0][mIndex][0] = d[0];
        pos[0][mIndex][1] = d[1];
        pos[0][mIndex][2] = d[2];
    }

    /*
     * PE
     */
    void LammpsVector3D::PE(IAPIVector *v) {

        pos[0][mIndex][0] += v->getX(0);
        pos[0][mIndex][1] += v->getX(1);
        pos[0][mIndex][2] += v->getX(2);
    }

    /*
     * PE
     */
    void LammpsVector3D::PE(double d) {
        pos[0][mIndex][0] += d;
        pos[0][mIndex][1] += d;
        pos[0][mIndex][2] += d;
    }

    /*
     * ME
     */
    void LammpsVector3D::ME(IAPIVector *v) {

        pos[0][mIndex][0] -= v->getX(0);
        pos[0][mIndex][1] -= v->getX(1);
        pos[0][mIndex][2] -= v->getX(2);
    }

    /*
     * TE
     */
    void LammpsVector3D::TE(IAPIVector *v) {

        pos[0][mIndex][0] *= v->getX(0);
        pos[0][mIndex][1] *= v->getX(1);
        pos[0][mIndex][2] *= v->getX(2);
    }

    /*
     * TE
     */
    void LammpsVector3D::TE(double d) {
        pos[0][mIndex][0] *= d;
        pos[0][mIndex][1] *= d;
        pos[0][mIndex][2] *= d;
    }

    /*
     * DE
     */
    void LammpsVector3D::DE(IAPIVector *v) {

        pos[0][mIndex][0] /= v->getX(0);
        pos[0][mIndex][1] /= v->getX(1);
        pos[0][mIndex][2] /= v->getX(2);
    }

    /*
     * Ea1Tv1
     */
    void LammpsVector3D::Ea1Tv1(double d, IAPIVector *v) {

        pos[0][mIndex][0] = d * v->getX(0);
        pos[0][mIndex][1] = d * v->getX(1);
        pos[0][mIndex][2] = d * v->getX(2);
    }

    /*
     * PEa1Tv1
     */
    void LammpsVector3D::PEa1Tv1(double d, IAPIVector *v) {

        pos[0][mIndex][0] += d * v->getX(0);
        pos[0][mIndex][1] += d * v->getX(1);
        pos[0][mIndex][2] += d * v->getX(2);
    }

    /*
     * Ev1Pv2
     */
    void LammpsVector3D::Ev1Pv2(IAPIVector *v1, IAPIVector *v2) {

        pos[0][mIndex][0] = v1->getX(0) + v2->getX(0);
        pos[0][mIndex][1] = v1->getX(1) + v2->getX(1);
        pos[0][mIndex][2] = v1->getX(2) + v2->getX(2);
    }

    /*
     * Ev1Mv2
     */
    void LammpsVector3D::Ev1Mv2(IAPIVector *v1, IAPIVector *v2) {

        pos[0][mIndex][0] = v1->getX(0) - v2->getX(0);
        pos[0][mIndex][1] = v1->getX(1) - v2->getX(1);
        pos[0][mIndex][2] = v1->getX(2) - v2->getX(2);
    }

    /*
     * mod
     */
    void LammpsVector3D::mod(IAPIVector *v) {
        while (pos[0][mIndex][0] > v->getX(0))
            pos[0][mIndex][0] -= v->getX(0);
        while (pos[0][mIndex][0] < 0.0)
            pos[0][mIndex][0] += v->getX(0);
        while (pos[0][mIndex][1] > v->getX(1))
            pos[0][mIndex][1] -= v->getX(1);
        while (pos[0][mIndex][1] < 0.0)
            pos[0][mIndex][1] += v->getX(1);
        while (pos[0][mIndex][2] > v->getX(2))
            pos[0][mIndex][2] -= v->getX(2);
        while (pos[0][mIndex][2] < 0.0)
            pos[0][mIndex][2] += v->getX(2);
    }

    /*
     * squared
     */
    double LammpsVector3D::squared() {

        return ((pos[0][mIndex][0] * pos[0][mIndex][0]) +
                (pos[0][mIndex][1] * pos[0][mIndex][1]) +
                (pos[0][mIndex][2] * pos[0][mIndex][2]));
    }

    /*
     * isZero
     */
    bool LammpsVector3D::isZero() {

        bool zero = false;

        if(pos[0][mIndex][0] == 0.0 && pos[0][mIndex][1] == 0.0 && pos[0][mIndex][2] == 0.0) {
            zero = true;
        }

        return zero;
    }

    /*
     * dot
     */
    double LammpsVector3D::dot(IAPIVector *v) {

        return ((pos[0][mIndex][0] * v->getX(0)) +
                (pos[0][mIndex][1] * v->getX(1)) +
                (pos[0][mIndex][2] * v->getX(2)));
    }

    /*
     * isNaN
     */
    bool LammpsVector3D::isNaN() {
        printf("WARNING : LammpsVector3D::isNaN() is not implemented.\n");
    }

    /*
     * Mv1Squared
     */
    double LammpsVector3D::Mv1Squared(IAPIVector *v) {

        double dx = pos[0][mIndex][0] - v->getX(0);
        double dy = pos[0][mIndex][1] - v->getX(1);
        double dz = pos[0][mIndex][2] - v->getX(2);

        return ((dx * dx) + (dy * dy) + (dz * dz));
    }

    /*
     * normalize
     */
    void LammpsVector3D::normalize() {
        double norm = 1.0 / sqrt(
                            ((pos[0][mIndex][0] * pos[0][mIndex][0]) +
                             (pos[0][mIndex][1] * pos[0][mIndex][1]) +
                             (pos[0][mIndex][2] * pos[0][mIndex][2])));
        pos[0][mIndex][0] *= norm;
        pos[0][mIndex][1] *= norm;
        pos[0][mIndex][2] *= norm;
    }

    /*
     * map
     */
    void LammpsVector3D::map(IAPIFunction *f) {
        printf("WARNING : LammpsVector3D::map() is not implemented.\n");
    }

    /*
     * XE
     */
   void LammpsVector3D::XE(IAPIVector *v) {
        double xNew = getX(1) * v->getX(2) - getX(2) * v->getX(1);
        double yNew = getX(2) * v->getX(0) - getX(0) * v->getX(2);
        pos[0][mIndex][2] = getX(0) * v->getX(1) - getX(1) * v->getX(0);
        pos[0][mIndex][1] = yNew;
        pos[0][mIndex][0] = xNew;
   }

    /*
     * E
     */
   void LammpsVector3D::E(double a, double b, double c) {
        pos[0][mIndex][0] = a;
        pos[0][mIndex][1] = b;
        pos[0][mIndex][2] = c;
   }

    /*
     * make3DArray
     */
    double *LammpsVector3D::make3DArray(double x, double y, double z) {
        double *nums;
        nums = (double *) malloc (sizeof(double) * 3);
        nums[0] = x;
        nums[1] = y;
        nums[2] = z;

        return nums;
    }

}
