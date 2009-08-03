/*
 *  GlotzillaVector2D.cpp
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

#include "IAPIVector.h"
#include "IAPIVector.h"

#include "GlotzillaVector2D.h"

namespace glotzwrappers
{

    GlotzillaVector2D::GlotzillaVector2D() {
        glotzVec = new glotzmath::glotz_vec();
        (*glotzVec)[0] = 0.0;
        (*glotzVec)[1] = 0.0;
        (*glotzVec)[2] = 0.0;
        D = 2;
    }

    GlotzillaVector2D::GlotzillaVector2D(double v1, double v2) {
        glotzVec = new glotzmath::glotz_vec();
        (*glotzVec)[0] = v1;
        (*glotzVec)[1] = v2;
        (*glotzVec)[2] = 0.0;
        D = 2;
    }

    GlotzillaVector2D::GlotzillaVector2D(glotzmath::glotz_vec *gVec) {
        glotzVec = gVec;
        D = 2;
    }

    GlotzillaVector2D::GlotzillaVector2D(GlotzillaVector2D *v) {
        glotzVec = new glotzmath::glotz_vec();
        this->E(v);
        D = 2;
    }

    GlotzillaVector2D::~GlotzillaVector2D() {
    }

    /*
     * getD
     */
    int GlotzillaVector2D::getD() {
        return D;
    }

    /*
     * assignTo
     */
    void GlotzillaVector2D::assignTo(double values[]) {
        values[0] = (*glotzVec)[0];
        values[1] = (*glotzVec)[1];
    }

    /*
     * equals
     */
    bool GlotzillaVector2D::equals(IAPIVector *v) {
        bool eq = false;

        if(v->getX(0) == (*glotzVec)[0] &&
           v->getX(1) == (*glotzVec)[1]) {
            eq = true;
        }

        return eq;
    }

    /*
     * x
     */
    double GlotzillaVector2D::getX(int index) {
        double value = 0.0;

        if(index == 0) {
            value = (*glotzVec)[0];
        }
        else if(index == 1) {
            value = (*glotzVec)[1];
        }

        return value;
    }

    /*
     * setX
     */
    void GlotzillaVector2D::setX(int index, double value) {
        if(index == 0) {
            (*glotzVec)[0] = value;
        }
        else if(index == 1) {
            (*glotzVec)[1] = value;
        }
    }

    /*
     * E
     */
    void GlotzillaVector2D::E(IAPIVector *v) {
        (*glotzVec)[0] = v->getX(0);
        (*glotzVec)[1] = v->getX(1);
        (*glotzVec)[2] = 0.0;
    }

    /*
     * E
     */
    void GlotzillaVector2D::E(double d) {
        (*glotzVec)[0] = d;
        (*glotzVec)[1] = d;
        (*glotzVec)[2] = 0.0;
    }

    /*
     * E
     */
    void GlotzillaVector2D::E(double d[]) {
        (*glotzVec)[0] = d[0];
        (*glotzVec)[1] = d[1];
        (*glotzVec)[2] = 0.0;
    }

    /*
     * PE
     */
    void GlotzillaVector2D::PE(IAPIVector *v) {

        (*glotzVec)[0] += v->getX(0);
        (*glotzVec)[1] += v->getX(1);
        (*glotzVec)[2] = 0.0;
    }

    /*
     * PE
     */
    void GlotzillaVector2D::PE(double d) {
        (*glotzVec)[0] += d;
        (*glotzVec)[1] += d;
        (*glotzVec)[2] = 0.0;
    }

    /*
     * ME
     */
    void GlotzillaVector2D::ME(IAPIVector *v) {

        (*glotzVec)[0] -= v->getX(0);
        (*glotzVec)[1] -= v->getX(1);
        (*glotzVec)[2] = 0.0;
    }

    /*
     * TE
     */
    void GlotzillaVector2D::TE(IAPIVector *v) {

        (*glotzVec)[0] *= v->getX(0);
        (*glotzVec)[1] *= v->getX(1);
        (*glotzVec)[2] = 0.0;
    }

    /*
     * TE
     */
    void GlotzillaVector2D::TE(double d) {
        (*glotzVec)[0] *= d;
        (*glotzVec)[1] *= d;
        (*glotzVec)[2] = 0.0;
    }

    /*
     * DE
     */
    void GlotzillaVector2D::DE(IAPIVector *v) {

        (*glotzVec)[0] /= v->getX(0);
        (*glotzVec)[1] /= v->getX(1);
        (*glotzVec)[2] = 0.0;
    }

    /*
     * Ea1Tv1
     */
    void GlotzillaVector2D::Ea1Tv1(double d, IAPIVector *v) {

        (*glotzVec)[0] = d * v->getX(0);
        (*glotzVec)[1] = d * v->getX(1);
        (*glotzVec)[2] = 0.0;
    }

    /*
     * PEa1Tv1
     */
    void GlotzillaVector2D::PEa1Tv1(double d, IAPIVector *v) {

        (*glotzVec)[0] += d * v->getX(0);
        (*glotzVec)[1] += d * v->getX(1);
        (*glotzVec)[2] = 0.0;
    }

    /*
     * Ev1Pv2
     */
    void GlotzillaVector2D::Ev1Pv2(IAPIVector *v1, IAPIVector *v2) {

        (*glotzVec)[0] = v1->getX(0) + v2->getX(0);
        (*glotzVec)[1] = v1->getX(1) + v2->getX(1);
        (*glotzVec)[2] = 0.0;
    }

    /*
     * Ev1Mv2
     */
    void GlotzillaVector2D::Ev1Mv2(IAPIVector *v1, IAPIVector *v2) {

        (*glotzVec)[0] = v1->getX(0) - v2->getX(0);
        (*glotzVec)[1] = v1->getX(1) - v2->getX(1);
        (*glotzVec)[2] = 0.0;
    }

    /*
     * mod
     */
    void GlotzillaVector2D::mod(IAPIVector *v) {

        while ((*glotzVec)[0] > v->getX(0))
            (*glotzVec)[0] -= v->getX(0);
        while ((*glotzVec)[0] < 0.0)
            (*glotzVec)[0] += v->getX(0);
        while ((*glotzVec)[1] > v->getX(1))
            (*glotzVec)[1] -= v->getX(1);
        while ((*glotzVec)[1] < 0.0)
            (*glotzVec)[1] += v->getX(1);
        (*glotzVec)[2] = 0.0;
    }

    /*
     * squared
     */
    double GlotzillaVector2D::squared() {

        return (((*glotzVec)[0] * (*glotzVec)[0]) +
                ((*glotzVec)[1] * (*glotzVec)[1]));
    }

    /*
     * isZero
     */
    bool GlotzillaVector2D::isZero() {

        bool zero = false;

        if((*glotzVec)[0] == 0.0 && (*glotzVec)[1] == 0.0) {
            zero = true;
        }

        return zero;
    }

    /*
     * dot
     */
    double GlotzillaVector2D::dot(IAPIVector *v) {

        return (((*glotzVec)[0] * v->getX(0)) +
                ((*glotzVec)[1] * v->getX(1)));
    }

    /*
     * isNaN
     */
    bool GlotzillaVector2D::isNaN() {
printf("WARNING : GlotzillaVector2D::isNaN() NOT implemented.\n");
    }

    /*
     * Mv1Squared
     */
    double GlotzillaVector2D::Mv1Squared(IAPIVector *v) {

        double dx = (*glotzVec)[0] - v->getX(0);
        double dy = (*glotzVec)[1] - v->getX(1);

        return ((dx * dx) + (dy * dy));
    }

    /*
     * normalize
     */
    void GlotzillaVector2D::normalize() {
        double norm = 1.0 / sqrt(
                            (((*glotzVec)[0] * (*glotzVec)[0]) +
                             ((*glotzVec)[1] * (*glotzVec)[1])));
        (*glotzVec)[0] *= norm;
        (*glotzVec)[1] *= norm;
        (*glotzVec)[2] = 0.0;
    }

    /*
     * map
     */
    void GlotzillaVector2D::map(IAPIFunction *f) {
printf("WARNING : GlotzillaVector2D::map() NOT implemented.\n");
    }

    /*
     * XE
     */
   void GlotzillaVector2D::XE(IAPIVector *v) {
printf("WARNING : GlotzillaVector2D::XE() NOT implemented.\n");
   }

}
