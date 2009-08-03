/*
 *  GlotzillaVector3D.cpp
 *  API Glue
 *
 */

#include <glotzmd.h>
#include <math.h>
#include <typeinfo>

#if defined(__MACH__) && defined(__APPLE__)
#include "stdlib.h"
#else
#include <malloc.h>
#endif

#include "GlotzillaVector3D.h"

namespace glotzwrappers
{

    GlotzillaVector3D::GlotzillaVector3D() {
        glotzVec = new glotzmath::glotz_vec();
        (*glotzVec)[0] = 0.0;
        (*glotzVec)[1] = 0.0;
        (*glotzVec)[2] = 0.0;
        D = 3;
    }

    GlotzillaVector3D::GlotzillaVector3D(double v1, double v2, double v3) {
        glotzVec = new glotzmath::glotz_vec();
        (*glotzVec)[0] = v1;
        (*glotzVec)[1] = v2;
        (*glotzVec)[2] = v3;
        D = 3;
    }

    GlotzillaVector3D::GlotzillaVector3D(glotzmath::glotz_vec *gVec) {
        glotzVec = gVec;
        D = 3;
    }

    GlotzillaVector3D::GlotzillaVector3D(GlotzillaVector3D *v) {
        glotzVec = new glotzmath::glotz_vec();
        this->E(v);
        D = 3;
    }

    GlotzillaVector3D::~GlotzillaVector3D() {
    }

    /*
     * getD
     */
    int GlotzillaVector3D::getD() {
        return D;
    }

    /*
     * assignTo
     */
    void GlotzillaVector3D::assignTo(double values[]) {
        values[0] = (*glotzVec)[0];
        values[1] = (*glotzVec)[1];
        values[2] = (*glotzVec)[2];
    }

    /*
     * equals
     */
    bool GlotzillaVector3D::equals(IAPIVector *v) {
        bool eq = false;

        if(v->getX(0) == (*glotzVec)[0] &&
           v->getX(1) == (*glotzVec)[1] &&
           v->getX(2) == (*glotzVec)[2]) {
            eq = true;
        }

        return eq;
    }

    /*
     * x
     */
    double GlotzillaVector3D::getX(int index) {
        double value = 0.0;

        if(index == 0) {
            value = (*glotzVec)[0];
        }
        else if(index == 1) {
            value = (*glotzVec)[1];
        }
        else {
            value = (*glotzVec)[2];
        }

        return value;
    }

    /*
     * setX
     */
    void GlotzillaVector3D::setX(int index, double value) {
        if(index == 0) {
            (*glotzVec)[0] = value;
        }
        else if(index == 1) {
            (*glotzVec)[1] = value;
        }
        else {
            (*glotzVec)[2] = value;
        }
    }

    /*
     * E
     */
    void GlotzillaVector3D::E(IAPIVector *v) {
        (*glotzVec)[0] = v->getX(0);
        (*glotzVec)[1] = v->getX(1);
        (*glotzVec)[2] = v->getX(2);
    }

    /*
     * E
     */
    void GlotzillaVector3D::E(double d) {
        (*glotzVec)[0] = d;
        (*glotzVec)[1] = d;
        (*glotzVec)[2] = d;
    }

    /*
     * E
     */
    void GlotzillaVector3D::E(double d[]) {
        (*glotzVec)[0] = d[0];
        (*glotzVec)[1] = d[1];
        (*glotzVec)[2] = d[2];
    }

    /*
     * PE
     */
    void GlotzillaVector3D::PE(IAPIVector *v) {

        (*glotzVec)[0] += v->getX(0);
        (*glotzVec)[1] += v->getX(1);
        (*glotzVec)[2] += v->getX(2);
    }

    /*
     * PE
     */
    void GlotzillaVector3D::PE(double d) {
        (*glotzVec)[0] += d;
        (*glotzVec)[1] += d;
        (*glotzVec)[2] += d;
    }

    /*
     * ME
     */
    void GlotzillaVector3D::ME(IAPIVector *v) {

        (*glotzVec)[0] -= v->getX(0);
        (*glotzVec)[1] -= v->getX(1);
        (*glotzVec)[2] -= v->getX(2);
    }

    /*
     * TE
     */
    void GlotzillaVector3D::TE(IAPIVector *v) {

        (*glotzVec)[0] *= v->getX(0);
        (*glotzVec)[1] *= v->getX(1);
        (*glotzVec)[2] *= v->getX(2);
    }

    /*
     * TE
     */
    void GlotzillaVector3D::TE(double d) {
        (*glotzVec)[0] *= d;
        (*glotzVec)[1] *= d;
        (*glotzVec)[2] *= d;
    }

    /*
     * DE
     */
    void GlotzillaVector3D::DE(IAPIVector *v) {

        (*glotzVec)[0] /= v->getX(0);
        (*glotzVec)[1] /= v->getX(1);
        (*glotzVec)[2] /= v->getX(2);
    }

    /*
     * Ea1Tv1
     */
    void GlotzillaVector3D::Ea1Tv1(double d, IAPIVector *v) {

        (*glotzVec)[0] = d * v->getX(0);
        (*glotzVec)[1] = d * v->getX(1);
        (*glotzVec)[2] = d * v->getX(2);
    }

    /*
     * PEa1Tv1
     */
    void GlotzillaVector3D::PEa1Tv1(double d, IAPIVector *v) {

        (*glotzVec)[0] += d * v->getX(0);
        (*glotzVec)[1] += d * v->getX(1);
        (*glotzVec)[2] += d * v->getX(2);
    }

    /*
     * Ev1Pv2
     */
    void GlotzillaVector3D::Ev1Pv2(IAPIVector *v1, IAPIVector *v2) {

        (*glotzVec)[0] = v1->getX(0) + v2->getX(0);
        (*glotzVec)[1] = v1->getX(1) + v2->getX(1);
        (*glotzVec)[2] = v1->getX(2) + v2->getX(2);
    }

    /*
     * Ev1Mv2
     */
    void GlotzillaVector3D::Ev1Mv2(IAPIVector *v1, IAPIVector *v2) {

        (*glotzVec)[0] = v1->getX(0) - v2->getX(0);
        (*glotzVec)[1] = v1->getX(1) - v2->getX(1);
        (*glotzVec)[2] = v1->getX(2) - v2->getX(2);
    }

    /*
     * mod
     */
    void GlotzillaVector3D::mod(IAPIVector *v) {

        while ((*glotzVec)[0] > v->getX(0))
            (*glotzVec)[0] -= v->getX(0);
        while ((*glotzVec)[0] < 0.0)
            (*glotzVec)[0] += v->getX(0);
        while ((*glotzVec)[1] > v->getX(1))
            (*glotzVec)[1] -= v->getX(1);
        while ((*glotzVec)[1] < 0.0)
            (*glotzVec)[1] += v->getX(1);
        while ((*glotzVec)[2] > v->getX(2))
            (*glotzVec)[2] -= v->getX(2);
        while ((*glotzVec)[2] < 0.0)
            (*glotzVec)[2] += v->getX(2);
    }

    /*
     * squared
     */
    double GlotzillaVector3D::squared() {

        return (((*glotzVec)[0] * (*glotzVec)[0]) +
                ((*glotzVec)[1] * (*glotzVec)[1]) +
                ((*glotzVec)[2] * (*glotzVec)[2]));
    }

    /*
     * isZero
     */
    bool GlotzillaVector3D::isZero() {

        bool zero = false;

        if((*glotzVec)[0] == 0.0 && (*glotzVec)[1] == 0.0 && (*glotzVec)[2] == 0.0) {
            zero = true;
        }

        return zero;
    }

    /*
     * dot
     */
    double GlotzillaVector3D::dot(IAPIVector *v) {

        return (((*glotzVec)[0] * v->getX(0)) +
                ((*glotzVec)[1] * v->getX(1)) +
                ((*glotzVec)[2] * v->getX(2)));
    }

    /*
     * isNaN
     */
    bool GlotzillaVector3D::isNaN() {
printf("WARNING : GlotzillaVector3D::isNaN() NOT implemented.\n");
    }

    /*
     * Mv1Squared
     */
    double GlotzillaVector3D::Mv1Squared(IAPIVector *v) {

        double dx = (*glotzVec)[0] - v->getX(0);
        double dy = (*glotzVec)[1] - v->getX(1);
        double dz = (*glotzVec)[2] - v->getX(2);

        return ((dx * dx) + (dy * dy) + (dz * dz));
    }

    /*
     * normalize
     */
    void GlotzillaVector3D::normalize() {
        double norm = 1.0 / sqrt(
                            (((*glotzVec)[0] * (*glotzVec)[0]) +
                             ((*glotzVec)[1] * (*glotzVec)[1]) +
                             ((*glotzVec)[2] * (*glotzVec)[2])));
        (*glotzVec)[0] *= norm;
        (*glotzVec)[1] *= norm;
        (*glotzVec)[2] *= norm;
    }

    /*
     * map
     */
    void GlotzillaVector3D::map(IAPIFunction *f) {
printf("WARNING : GlotzillaVector3D::map() NOT implemented.\n");
    }

    /*
     * XE
     */
   void GlotzillaVector3D::XE(IAPIVector *v) {
        double xNew = getX(1) * v->getX(2) - getX(2) * v->getX(1);
        double yNew = getX(2) * v->getX(0) - getX(0) * v->getX(2);
        (*glotzVec)[2] = getX(0) * v->getX(1) - getX(1) * v->getX(0);
        (*glotzVec)[1] = yNew;
        (*glotzVec)[0] = xNew;
   }

    /*
     * E
     */
   void GlotzillaVector3D::E(double a, double b, double c) {
        (*glotzVec)[0] = a;
        (*glotzVec)[1] = b;
        (*glotzVec)[2] = c;
   }

    /*
     * make3DArray
     */
    double *GlotzillaVector3D::make3DArray(double x, double y, double z) {
        double *nums;
        nums = (double *) malloc (sizeof(double) * 3);
        nums[0] = x;
        nums[1] = y;
        nums[2] = z;

        return nums;
    }

}
