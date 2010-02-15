/*
 *  LammpsBoundaryShrink.cpp
 *  API Glue
 *
 */

#include "library.h"

#include "LammpsBoundaryShrink.h"

namespace lammpssnifferwrappers
{

    LammpsBoundaryShrink::LammpsBoundaryShrink(LammpsSimulation *sim) : LammpsBoundary(sim) {
    }

    /*
     * getEdgeVector()
     */
    IAPIVector *LammpsBoundaryShrink::getEdgeVector(int d) {

        IAPIVector *bound = getBoxSize();

        IAPIVectorMutable *edge = NULL;

        if(d < mSim->getSpace()->getD()) {
            edge = mSim->getSpace()->makeVector();
            double vals[mSim->getSpace()->getD()];
            for(int i = 0; i < mSim->getSpace()->getD(); i++) {
                vals[i] = 0.0;
            }
            vals[d] = bound->getX(d);
            edge->E(vals);
        }

        return edge;

    }

    /*
     * getPeriodicity()
     */
    bool LammpsBoundaryShrink::getPeriodicity(int d) {
        return false;
    }

}

