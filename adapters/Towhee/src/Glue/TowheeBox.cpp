/*
 *  TowheeBox.cpp
 *  API Glue
 *
 *
 */

#include "stdio.h"

#include "IAPIAtom.h"
#include "IAPIBox.h"
#include "IAPISimulation.h"
#include "IAPIVector.h"
#include "IAPIMolecule.h"
#include "TowheeBox.h"

namespace towheewrappers
{

    TowheeBox::TowheeBox() {
    }

    /*
     * setIndex()
     */
    void TowheeBox::setIndex(int newIndex) {
        mIndex = newIndex;
    }

    /*
     * getIndex()
     */
    int TowheeBox::getIndex() {
        return mIndex;
    }

    /*
     * addMolecule()
     */
    void TowheeBox::addMolecule(IAPIMolecule *mole) {
printf("WARNING : TowheeBox::addMolecule() not implemented.\n"); fflush(stdout);
    }

    /*
     * removeMolecule()
     */
    void TowheeBox::removeMolecule(IAPIMolecule *mole) {
printf("WARNING : TowheeBox::removeMolecule() not implemented.\n"); fflush(stdout);
    }

    /*
     * setNMolecules()
     */
    void TowheeBox::setNMolecules(IAPISpecies *species, int numMolecules) {
printf("WARNING : TowheeBox::setNMolecules() not implemented.\n"); fflush(stdout);
    }

    /*
     * getNMolecules()
     */
    int TowheeBox::getNMolecules(IAPISpecies *species) {
printf("WARNING : TowheeBox::getNMolecules() not implemented.\n"); fflush(stdout);
    }

    /*
     * getMoleculeList()
     */
    IAPIMoleculeList *TowheeBox::getMoleculeList(IAPISpecies *species) {
printf("WARNING : TowheeBox::getMoleculeList() not implemented.\n"); fflush(stdout);
    }

    /*
     * getMoleculeList()
     */
    IAPIMoleculeList *TowheeBox::getMoleculeList() {
printf("WARNING : TowheeBox::getMoleculeList() not implemented.\n"); fflush(stdout);
    }

    /*
     * getLeafList()
     */
    IAPIAtomList *TowheeBox::getLeafList() {
printf("WARNING : TowheeBox::getLeafList() not implemented.\n"); fflush(stdout);
    }

    /*
     * getBoundary()
     */
    IAPIBoundary *TowheeBox::getBoundary() {
        return mBoundary;
    }

    /*
     * setBoundary()
     */
    void TowheeBox::setBoundary(IAPIBoundary *boundary) {
        mBoundary = boundary;
    }

    /*
     * getEventManager()
     */
    IAPIBoxEventManager *TowheeBox::getEventManager() {
printf("WARNING : TowheeBox::getEventManager() not implemented.\n"); fflush(stdout);
    }

    /*
     * addSpeciesNotify()
     */
    void TowheeBox::addSpeciesNotify(IAPISpecies *species) {
printf("WARNING : TowheeBox::addSpeciesNotify() not implemented.\n"); fflush(stdout);
    }

    /*
     * removeSpeciesNotify()
     */
    void TowheeBox::removeSpeciesNotify(IAPISpecies *species) {
printf("WARNING : TowheeBox::removeSpeciesNotify() not implemented.\n"); fflush(stdout);
    }


}
