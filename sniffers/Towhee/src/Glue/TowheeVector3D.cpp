/*
 *  TowheeVector3D.cpp
 *  API Glue
 *
 */

#include "stdio.h"

#include "TowheeVector3D.h"

namespace towheesnifferwrappers
{

    TowheeVector3D::TowheeVector3D() {
        D = 3;
        vecPos[0] = 0.0;
        vecPos[1] = 0.0;
        vecPos[2] = 0.0;
    }

    TowheeVector3D::TowheeVector3D(double x, double y, double z) {
        D = 3;
        vecPos[0] = x;
        vecPos[1] = y;
        vecPos[2] = z;
    }

    /*
     * assignTo
     */
    void TowheeVector3D::assignTo(double values[]) {
        values[0] = vecPos[0];
        values[1] = vecPos[1];
        values[2] = vecPos[2];
    }

    /*
     * equals
     */
    bool TowheeVector3D::equals(IAPIVector *v) {
    }

    /*
     * x
     */
    double TowheeVector3D::getX(int index) {
        return vecPos[index];
    }

    /*
     * setX
     */
    void TowheeVector3D::setX(int index, double value) {
        vecPos[index] = value;
    }

    /*
     * E
     */
    void TowheeVector3D::E(IAPIVector *v) {
        vecPos[0] = v->getX(0);
        vecPos[1] = v->getX(1);
        vecPos[2] = v->getX(2);
    }

    /*
     * E
     */
    void TowheeVector3D::E(double d) {
        vecPos[0] = d;
        vecPos[1] = d;
        vecPos[2] = d;
    }

    /*
     * E
     */
    void TowheeVector3D::E(double d[]) {
        vecPos[0] = d[0];
        vecPos[1] = d[1];
        vecPos[2] = d[2];
    }

    /*
     * PE
     */
    void TowheeVector3D::PE(IAPIVector *v) {
        vecPos[0] += v->getX(0);
        vecPos[1] += v->getX(1);
        vecPos[2] += v->getX(2);
    }

    /*
     * PE
     */
    void TowheeVector3D::PE(double d) {
        vecPos[0] += d;
        vecPos[1] += d;
        vecPos[2] += d;
    }

    /*
     * ME
     */
    void TowheeVector3D::ME(IAPIVector *v) {
        vecPos[0] -= v->getX(0);
        vecPos[1] -= v->getX(1);
        vecPos[2] -= v->getX(2);
    }

    /*
     * TE
     */
    void TowheeVector3D::TE(IAPIVector *v) {
        vecPos[0] *= v->getX(0);
        vecPos[1] *= v->getX(1);
        vecPos[2] *= v->getX(2);
    }

    /*
     * TE
     */
    void TowheeVector3D::TE(double d) {
        vecPos[0] *= d;
        vecPos[1] *= d;
        vecPos[2] *= d;
    }

    /*
     * DE
     */
    void TowheeVector3D::DE(IAPIVector *v) {
        vecPos[0] /= v->getX(0);
        vecPos[1] /= v->getX(1);
        vecPos[2] /= v->getX(2);
    }

    /*
     * Ea1Tv1
     */
    void TowheeVector3D::Ea1Tv1(double d, IAPIVector *v) {
        vecPos[0] = d * v->getX(0);
        vecPos[1] = d * v->getX(1);
        vecPos[2] = d * v->getX(2);
    }

    /*
     * PEa1Tv1
     */
    void TowheeVector3D::PEa1Tv1(double d, IAPIVector *v) {
        vecPos[0] += d * v->getX(0);
        vecPos[1] += d * v->getX(1);
        vecPos[2] += d * v->getX(2);
    }

    /*
     * Ev1Pv2
     */
    void TowheeVector3D::Ev1Pv2(IAPIVector *v1, IAPIVector *v2) {
        vecPos[0] = v1->getX(0) + v2->getX(0);
        vecPos[1] = v1->getX(1) + v2->getX(1);
        vecPos[2] = v1->getX(2) + v2->getX(2);
    }

    /*
     * Ev1Mv2
     */
    void TowheeVector3D::Ev1Mv2(IAPIVector *v1, IAPIVector *v2) {
        vecPos[0] = v1->getX(0) - v2->getX(0);
        vecPos[1] = v1->getX(1) - v2->getX(1);
        vecPos[2] = v1->getX(2) - v2->getX(2);
    }

    /*
     * mod
     */
    void TowheeVector3D::mod(IAPIVector *v) {
        while (vecPos[0] > v->getX(0))
            vecPos[0] -= v->getX(0);
        while (vecPos[0] < 0.0)
            vecPos[0] += v->getX(0);
        while (vecPos[1] > v->getX(1))
            vecPos[1] -= v->getX(1);
        while (vecPos[1] < 0.0)
            vecPos[1] += v->getX(1);
        while (vecPos[2] > v->getX(2))
            vecPos[2] -= v->getX(2);
        while (vecPos[2] < 0.0)
            vecPos[2] += v->getX(2);
    }

    /*
     * squared
     */
    double TowheeVector3D::squared() {
        return (vecPos[0] * vecPos[0] +
                vecPos[1] * vecPos[1] +
                vecPos[2] * vecPos[2]);
    }

    /*
     * isZero
     */
    bool TowheeVector3D::isZero() {
    }

    /*
     * dot
     */
    double TowheeVector3D::dot(IAPIVector *v) {
    }

    /*
     * isNaN
     */
    bool TowheeVector3D::isNaN() {
    }

    /*
     * Mv1Squared
     */
    double TowheeVector3D::Mv1Squared(IAPIVector *v) {
    }

    /*
     * normalize
     */
    void TowheeVector3D::normalize() {
    }

    /*
     * map
     */
    void TowheeVector3D::map(IAPIFunction *f) {
    }

    /*
     * XE
     */
   void TowheeVector3D::XE(IAPIVector *v) {
   }

    /*
     * E
     */
   void TowheeVector3D::E(double a, double b, double c) {
   }


}
