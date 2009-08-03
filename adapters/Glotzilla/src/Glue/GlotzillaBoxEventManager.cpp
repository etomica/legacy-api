/*
 *  GlotzillaBoxEventManager.cpp
 *  API  Glue
 *
 */

#include "stdio.h"

#include "GlotzillaBoxAtomEvent.h"
#include "GlotzillaBoxMoleculeEvent.h"
#include "GlotzillaBoxIndexEvent.h"
#include "GlotzillaBoxAtomIndexEvent.h"
#include "GlotzillaBoxMoleculeCountEvent.h"
#include "GlotzillaBoxMoleculeIndexEvent.h"

#include "GlotzillaBoxEventManager.h"

namespace glotzwrappers
{

    /*
     * addListener()
     */
    void GlotzillaBoxEventManager::addListener(IAPIBoxListener *listener) {
        listeners.push_back(listener);
    }

    /*
     * removeListener()
     */
    void GlotzillaBoxEventManager::removeListener(IAPIBoxListener *listener) {
printf("GlotzillaBoxEventManager::removeListener() is NOT implemented.\n"); fflush(stdout);
//        listeners.remove(listener);
    }

    /*
     * atomAdded()
     */
    void GlotzillaBoxEventManager::atomAdded(IAPIBox *box, IAPIAtom *atom) {
        GlotzillaBoxAtomEvent *event = new GlotzillaBoxAtomEvent(atom, box);
        for(int i = 0; i < listeners.size(); i++) {
            listeners.at(i)->boxAtomAdded(event);
        }
    }
    /*
     * atomRemoved()
     */
    void GlotzillaBoxEventManager::atomRemoved(IAPIBox *box, IAPIAtom *atom) {
        GlotzillaBoxAtomEvent *event = new GlotzillaBoxAtomEvent(atom, box);
        for(int i = 0; i < listeners.size(); i++) {
            listeners.at(i)->boxAtomRemoved(event);
        }
    }
    /*
     * moleculeAdded()
     */
    void GlotzillaBoxEventManager::moleculeAdded(IAPIBox *box, IAPIMolecule *molecule) {
        GlotzillaBoxMoleculeEvent *event = new GlotzillaBoxMoleculeEvent(molecule, box);
        for(int i = 0; i < listeners.size(); i++) {
            listeners.at(i)->boxMoleculeAdded(event);
        }
    }
    /*
     * moleculeRemoved()
     */
    void GlotzillaBoxEventManager::moleculeRemoved(IAPIBox *box, IAPIMolecule *molecule) {
        GlotzillaBoxMoleculeEvent *event = new GlotzillaBoxMoleculeEvent(molecule, box);
        for(int i = 0; i < listeners.size(); i++) {
            listeners.at(i)->boxMoleculeRemoved(event);
        }
    }
    /*
     * globalAtomIndexChanged()
     */
    void GlotzillaBoxEventManager::globalAtomIndexChanged(IAPIBox *box, int index) {
        GlotzillaBoxIndexEvent *event = new GlotzillaBoxIndexEvent(index, box);
        for(int i = 0; i < listeners.size(); i++) {
            listeners.at(i)->boxGlobalAtomIndexChanged(event);
        }
    }
    /*
     * globalAtomLeafIndexChanged()
     */
    void GlotzillaBoxEventManager::globalAtomLeafIndexChanged(IAPIBox *box, int index) {
        GlotzillaBoxIndexEvent *event = new GlotzillaBoxIndexEvent(index, box);
        for(int i = 0; i < listeners.size(); i++) {
            listeners.at(i)->boxGlobalAtomLeafIndexChanged(event);
        }
    }
    /*
     * atomLeafIndexChanged()
     */
    void GlotzillaBoxEventManager::atomLeafIndexChanged(IAPIBox *box, IAPIAtom *atom, int index) {
        GlotzillaBoxAtomIndexEvent *event = new GlotzillaBoxAtomIndexEvent(atom, index, box);
        for(int i = 0; i < listeners.size(); i++) {
            listeners.at(i)->boxAtomLeafIndexChanged(event);
        }
    }
    /*
     * numberMolecules()
     */
    void GlotzillaBoxEventManager::numberMolecules(IAPIBox *box, IAPISpecies *species, int count) {
        GlotzillaBoxMoleculeCountEvent *event = new GlotzillaBoxMoleculeCountEvent(species, count, box);
        for(int i = 0; i < listeners.size(); i++) {
            listeners.at(i)->boxNumberMolecules(event);
        }
    }
    /*
     * moleculeIndexChanged()
     */
    void GlotzillaBoxEventManager::moleculeIndexChanged(IAPIBox *box, IAPIMolecule *molecule, int index) {
        GlotzillaBoxMoleculeIndexEvent *event = new GlotzillaBoxMoleculeIndexEvent(molecule, index, box);
        for(int i = 0; i < listeners.size(); i++) {
            listeners.at(i)->boxMoleculeIndexChanged(event);
        }
    }

}
