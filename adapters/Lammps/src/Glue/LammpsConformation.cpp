/*
 *  LammpsConformation.cpp
 *  API Glue
 *
 */

#include "stdio.h"
#include <math.h>

#include "IAPIAtomPositioned.h"
#include "IAPIVector.h"
#include "LammpsConformation.h"
#include "LammpsAtom.h"
#include "LammpsVector3D.h"

namespace lammpswrappers
{

    LammpsConformation::LammpsConformation(IAPISimulation *sim) {
        mSim = dynamic_cast<LammpsSimulation *>(sim);
    }

    /*
     * initializePositions()
     */
    void LammpsConformation::initializePositions(IAPIAtomList *as) {
printf("LammpsConformation::initializePositions() -> Ah, NOT OK.\n");
        double PI = 3.14159265;
        int nLeaf = as->getAtomCount();
        if(nLeaf ==0) return;

        double xNext = -0.55*0.5*(nLeaf-1);
        for (int iLeaf=0; iLeaf<nLeaf; iLeaf++) {
            LammpsAtom *a = dynamic_cast<LammpsAtom *>(as->getAtom(iLeaf));
            LammpsVector3D *orientation = new LammpsVector3D(sin(0.0)*cos(45.0*PI/180.0),
                                                  sin(45.0*PI/180.0)*sin(0.0),
                                                  cos(45.0*PI/180.0));
            IAPIVectorMutable *pos = a->getPosition();
            pos->Ea1Tv1(xNext, orientation);
            a->getPosition()->E(pos);
            xNext += 0.55;
        }
    }

}
