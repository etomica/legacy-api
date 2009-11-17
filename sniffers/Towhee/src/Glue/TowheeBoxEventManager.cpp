/*
 *  TowheeBoxEventManager.cpp
 *  API  Glue
 *
 */

#include "TowheeBoxEventManager.h"

namespace towheesnifferwrappers
{

    /*
     * addListener()
     */
    void TowheeBoxEventManager::addListener(IAPIBoxListener *listener) {
    }

    /*
     * removeListener()
     */
    void TowheeBoxEventManager::removeListener(IAPIBoxListener *listener) {
    }

    /*
     * atomAdded()
     */
    void TowheeBoxEventManager::atomAdded(IAPIBox *box, IAPIAtom *atom) {
    }
    /*
     * atomRemoved()
     */
    void TowheeBoxEventManager::atomRemoved(IAPIBox *box, IAPIAtom *atom) {
    }
    /*
     * moleculeAdded()
     */
    void TowheeBoxEventManager::moleculeAdded(IAPIBox *box, IAPIMolecule *molecule) {
    }
    /*
     * moleculeRemoved()
     */
    void TowheeBoxEventManager::moleculeRemoved(IAPIBox *box, IAPIMolecule *molecule) {
    }
    /*
     * globalAtomIndexChanged()
     */
    void TowheeBoxEventManager::globalAtomIndexChanged(IAPIBox *box, int index) {
    }
    /*
     * globalAtomLeafIndexChanged()
     */
    void TowheeBoxEventManager::globalAtomLeafIndexChanged(IAPIBox *box, int index) {
    }
    /*
     * atomLeafIndexChanged()
     */
    void TowheeBoxEventManager::atomLeafIndexChanged(IAPIBox *box, IAPIAtom *atom, int index) {
    }
    /*
     * numberMolecules()
     */
    void TowheeBoxEventManager::numberMolecules(IAPIBox *box, IAPISpecies *species, int count) {
    }
    /*
     * moleculeIndexChanged()
     */
    void TowheeBoxEventManager::moleculeIndexChanged(IAPIBox *box, IAPIMolecule *molecule, int index) {
    }

}
