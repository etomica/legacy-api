/*
 *  GlotzillaBoxEventManager.h
 *  API Glue
 *
 */

#ifndef GLOTZ_BOXEVENTMGR_WRAPPER_H
#define GLOTZ_BOXEVENTMGR_WRAPPER_H

#include <vector>

#include "IAPIBoxEventManager.h"
#include "IAPIBoxListener.h"

using namespace molesimAPI;

namespace glotzwrappers
{

    /**
      * GlotzillaBoxEventManager fires box events to any listeners
      * registered to receive box events.  A listener is notified of any box
      * event whether the listener is interested in the event or not.  If
      * the listener is not interested in the event, it can ignore the event.
      * The listener determines the kind of event by checking the type of
      * the event class.
      */
    class GlotzillaBoxEventManager : public virtual IAPIBoxEventManager {

        public:
            /**
              * Register a box listener to receive box events.
              * @param listener Box listener to receive events.
              */
            void addListener(IAPIBoxListener *listener);
            /**
              * Unregister a box listener from receiving box events.
              * @param listener Box listener to unregister.
              */
            void removeListener(IAPIBoxListener *listener);

            // Non-API
            void atomAdded(IAPIBox *box, IAPIAtom *atom);
            void atomRemoved(IAPIBox *box, IAPIAtom *atom);
            void moleculeAdded(IAPIBox *box, IAPIMolecule *molecule);
            void moleculeRemoved(IAPIBox *box, IAPIMolecule *molecule);
            void globalAtomIndexChanged(IAPIBox *box, int index);
            void globalAtomLeafIndexChanged(IAPIBox *box, int index);
            void atomLeafIndexChanged(IAPIBox *box, IAPIAtom *atom, int index);
            void numberMolecules(IAPIBox *box, IAPISpecies *species, int count);
            void moleculeIndexChanged(IAPIBox *box, IAPIMolecule *molecule, int index);

        protected:
            std::vector<IAPIBoxListener *> listeners;
    };
}

#endif
