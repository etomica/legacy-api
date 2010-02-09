/*
 *  LammpsVector2D.cpp
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

#include "IAPIVector.h"
#include "IAPIFunction.h"
#include "LammpsVector2D.h"

#include <typeinfo>
#include "LammpsVector3D.h"

namespace lammpssnifferwrappers
{

    LammpsVector2D::LammpsVector2D() {
        D = 2;
        pos = (double **) malloc (1 * sizeof(double *));
        pos[0] = (double *) malloc (D * sizeof(double));

        for(int i = 0; i < D; i++) {
            pos[0][i] = 0.0;
        }
    }

/*
    LammpsVector2D::LammpsVector2D(double v1, double v2) {
        D = 2;
        pos = (double *) malloc (D * sizeof(double));
        (pos)[0] = v1;
        (pos)[1] = v2;
    }

    LammpsVector2D::LammpsVector2D(LammpsVector2D *v) {
        D = 2;
        pos = (double *) malloc (D * sizeof(double));
        this->E(v);
    }
*/
    LammpsVector2D::LammpsVector2D(double **v) {
        pos = v;
        D = 2;
    }

    /*
     * getD
     */
    int LammpsVector2D::getD() {
        return D;
    }

    /*
     * assignTo
     */
    void LammpsVector2D::assignTo(double values[]) {
        values[0] = pos[0][0];
        values[1] = pos[0][1];
    }

    /*
     * equals
     */
    bool LammpsVector2D::equals(IAPIVector *v) {
        bool eq = false;

        if(v->getX(0) == pos[0][0] &&
           v->getX(1) == pos[0][1]) {
            eq = true;
        }

        return eq;
    }

    /*
     * x
     */
    double LammpsVector2D::getX(int index) {
        double value = 0.0;
        if(index == 0) {
            value = pos[0][0];
        }
        else if(index == 1) {
            value = pos[0][1];
        }

        return value;
    }

    /*
     * setX
     */
    void LammpsVector2D::setX(int index, double value) {
        if(index == 0) {
            pos[0][0] = value;
        }
        else if(index == 1) {
            pos[0][1] = value;
        }
    }

    /*
     * E
     */
    void LammpsVector2D::E(IAPIVector *v) {
        pos[0][0] = v->getX(0);
        pos[0][1] = v->getX(1);
    }

    /*
     * E
     */
    void LammpsVector2D::E(double d) {
        pos[0][0] = d;
        pos[0][1] = d;
    }

    /*
     * E
     */
    void LammpsVector2D::E(double d[]) {
        pos[0][0] = d[0];
        pos[0][1] = d[1];
    }

    /*
     * PE
     */
    void LammpsVector2D::PE(IAPIVector *v) {

        pos[0][0] += v->getX(0);
        pos[0][1] += v->getX(1);
    }

    /*
     * PE
     */
    void LammpsVector2D::PE(double d) {
        pos[0][0] += d;
        pos[0][1] += d;
    }

    /*
     * ME
     */
    void LammpsVector2D::ME(IAPIVector *v) {

        pos[0][0] -= v->getX(0);
        pos[0][1] -= v->getX(1);
    }

    /*
     * TE
     */
    void LammpsVector2D::TE(IAPIVector *v) {

        pos[0][0] *= v->getX(0);
        pos[0][1] *= v->getX(1);
    }

    /*
     * TE
     */
    void LammpsVector2D::TE(double d) {
        pos[0][0] *= d;
        pos[0][1] *= d;
    }

    /*
     * DE
     */
    void LammpsVector2D::DE(IAPIVector *v) {

        pos[0][0] /= v->getX(0);
        pos[0][1] /= v->getX(1);
    }

    /*
     * Ea1Tv1
     */
    void LammpsVector2D::Ea1Tv1(double d, IAPIVector *v) {

        pos[0][0] = d * v->getX(0);
        pos[0][1] = d * v->getX(1);
    }

    /*
     * PEa1Tv1
     */
    void LammpsVector2D::PEa1Tv1(double d, IAPIVector *v) {

        pos[0][0] += d * v->getX(0);
        pos[0][1] += d * v->getX(1);
    }

    /*
     * Ev1Pv2
     */
    void LammpsVector2D::Ev1Pv2(IAPIVector *v1, IAPIVector *v2) {

        pos[0][0] = v1->getX(0) + v2->getX(0);
        pos[0][1] = v1->getX(1) + v2->getX(1);
    }

    /*
     * Ev1Mv2
     */
    void LammpsVector2D::Ev1Mv2(IAPIVector *v1, IAPIVector *v2)
 {
        pos[0][0] = v1->getX(0) - v2->getX(0);
        pos[0][1] = v1->getX(1) - v2->getX(1);
    }

    /*
     * mod
     */
    void LammpsVector2D::mod(IAPIVector *v) {

        while (pos[0][0] > v->getX(0))
            pos[0][0] -= v->getX(0);
        while (pos[0][0] < 0.0)
            pos[0][0] += v->getX(0);
        while (pos[0][1] > v->getX(1))
            pos[0][1] -= v->getX(1);
        while (pos[0][1] < 0.0)
            pos[0][1] += v->getX(1);
    }

    /*
     * squared
     */
    double LammpsVector2D::squared() {

        return ((pos[0][0] * pos[0][0]) +
                (pos[0][1] * pos[0][1]));
    }

    /*
     * isZero
     */
    bool LammpsVector2D::isZero() {

        bool zero = false;

        if(pos[0][0] == 0.0 && pos[0][1] == 0.0) {
            zero = true;
        }

        return zero;
    }

    /*
     * dot
     */
    double LammpsVector2D::dot(IAPIVector *v) {

        return ((pos[0][0] * v->getX(0)) +
                (pos[0][1] * v->getX(1)));
    }

    /*
     * isNaN
     */
    bool LammpsVector2D::isNaN() {
printf("WARNING : LammpsVector2D::isNaN() NOT implemented.\n");
    }

    /*
     * Mv1Squared
     */
    double LammpsVector2D::Mv1Squared(IAPIVector *v) {

        double dx = pos[0][0] - v->getX(0);
        double dy = pos[0][1] - v->getX(1);

        return ((dx * dx) + (dy * dy));
    }

    /*
     * normalize
     */
    void LammpsVector2D::normalize() {
        double norm = 1.0 / sqrt(
                            ((pos[0][0] * pos[0][0]) +
                             (pos[0][1] * pos[0][1])));
        pos[0][0] *= norm;
        pos[0][1] *= norm;
    }

    /*
     * map
     */
    void LammpsVector2D::map(IAPIFunction *f) {
printf("WARNING : LammpsVector2D::map() NOT implemented.\n");
    }

    /*
     * XE
     */
   void LammpsVector2D::XE(IAPIVector *v) {
printf("WARNING : LammpsVector2D::XE() NOT implemented.\n");
   }

    /*
     * E
     */
    void LammpsVector2D::E(double x, double y) {
        pos[0][0] = x;
        pos[0][1] = y;
    }

}
