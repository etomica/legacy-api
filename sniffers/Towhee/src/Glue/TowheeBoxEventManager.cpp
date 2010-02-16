/*
 *  TowheeBoxEventManager.cpp
 *  API  Glue
 *
 */

#include "stdio.h"

#include "TowheeBoxEventManager.h"

namespace towheesnifferwrappers
{

    /*
     * addListener()
     */
    void TowheeBoxEventManager::addListener(IAPIBoxListener *listener) {
        printf("TowheeBoxEventManager::addListener(IAPIBoxListener *) is not implemented.\n");
    }

    /*
     * removeListener()
     */
    void TowheeBoxEventManager::removeListener(IAPIBoxListener *listener) {
        printf("TowheeBoxEventManager::removeListener(IAPIBoxListener *) is not implemented.\n");
    }

    /*
     * atomAdded()
     */
    void TowheeBoxEventManager::atomAdded(IAPIBox *box, IAPIAtom *atom) {
        printf("TowheeBoxEventManager::atomAdded(IAPIBox *, IAPIAtom *) is not implemented.\n");
    }
    /*
     * atomRemoved()
     */
    void TowheeBoxEventManager::atomRemoved(IAPIBox *box, IAPIAtom *atom) {
        printf("TowheeBoxEventManager::atomRemoved(IAPIBox *, IAPIAtom *) is not implemented.\n");
    }
    /*
     * moleculeAdded()
     */
    void TowheeBoxEventManager::moleculeAdded(IAPIBox *box, IAPIMolecule *molecule) {
        printf("TowheeBoxEventManager::moleculeAdded(IAPIBox *, IAPIMolecule *) is not implemented.\n");
    }
    /*
     * moleculeRemoved()
     */
    void TowheeBoxEventManager::moleculeRemoved(IAPIBox *box, IAPIMolecule *molecule) {
        printf("TowheeBoxEventManager::moleculeRemoved(IAPIBox *, IAPIMolecule *) is not implemented.\n");
    }
    /*
     * globalAtomIndexChanged()
     */
    void TowheeBoxEventManager::globalAtomIndexChanged(IAPIBox *box, int index) {
        printf("TowheeBoxEventManager::globalAtomIndexChanged(IAPIBox *, int) is not implemented.\n");
    }
    /*
     * globalAtomLeafIndexChanged()
     */
    void TowheeBoxEventManager::globalAtomLeafIndexChanged(IAPIBox *box, int index) {
        printf("TowheeBoxEventManager::globalAtomLeafIndexChanged(IAPIBox *, int) is not implemented.\n");
    }
    /*
     * atomLeafIndexChanged()
     */
    void TowheeBoxEventManager::atomLeafIndexChanged(IAPIBox *box, IAPIAtom *atom, int index) {
        printf("TowheeBoxEventManager::atomLeafIndexChanged(IAPIBox *, IAPIAtom *, int) is not implemented.\n");
    }
    /*
     * numberMolecules()
     */
    void TowheeBoxEventManager::numberMolecules(IAPIBox *box, IAPISpecies *species, int count) {
        printf("TowheeBoxEventManager::numberMolecules(IAPIBox *, IAPISpecies *, int) is not implemented.\n");
    }
    /*
     * moleculeIndexChanged()
     */
    void TowheeBoxEventManager::moleculeIndexChanged(IAPIBox *box, IAPIMolecule *molecule, int index) {
        printf("TowheeBoxEventManager::moleculeIndexChanged(IAPIBox *, IAPIMolecule *, int) is not implemented.\n");
    }

}
