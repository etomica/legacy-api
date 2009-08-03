/*
 *  GlotzillaSpring.cpp
 *  API Glue
 *
 */

#include <glotzmd.h>

#include "GlotzillaSpring.h"

namespace glotzwrappers
{

    GlotzillaSpring::GlotzillaSpring() {
        mSpring = 0.7;
        mExtent = 0.5;
    }

    GlotzillaSpring::GlotzillaSpring(double spring, double extent) {
        mSpring = spring;
        mExtent = extent;
    }

    /*
     * getRange()
     */
    double GlotzillaSpring::getRange() {
printf("WARNING : GlotzillaSpring::getRange() is NOT implemented.\n");
    }

    /*
     * energy()
     */
    double GlotzillaSpring::energy(IAPIAtomList *as) {
printf("WARNING : GlotzillaSpring::energy() is NOT implemented.\n");
    }

    /*
     * nBody()
     */
    int GlotzillaSpring::nBody() {
printf("WARNING : GlotzillaSpring::nBody() is NOT implemented.\n");
        return 2;
    }

    /*
     * setBox()
     */
    void GlotzillaSpring::setBox(IAPIBox *box) {
printf("WARNING : GlotzillaSpring::setBox() is NOT implemented.\n");
    }

    /*
     * setSpringConstant()
     */
    void GlotzillaSpring::setSpringConstant(double spring) {
        mSpring = spring;
    }

    /*
     * setTargetExtent()
     */
    void GlotzillaSpring::setTargetExtent(double extent) {
        mExtent = extent;
    }

    /*
     * getSpringConstant()
     */
    double GlotzillaSpring::getSpringConstant() {
        return mSpring;
    }

    /*
     * getTargetExtent()
     */
    double GlotzillaSpring::getTargetExtent() {
        return mExtent;
    }

}
