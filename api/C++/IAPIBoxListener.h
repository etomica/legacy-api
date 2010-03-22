/*
 *  IAPIBoxListener.h
 *  API Glue
 *
 */

#ifndef API_IBOXLISTENER_WRAPPER_H
#define API_IBOXLISTENER_WRAPPER_H

#include "IAPIBoxAtomEvent.h"
#include "IAPIBoxAtomIndexEvent.h"
#include "IAPIBoxIndexEvent.h"
#include "IAPIBoxMoleculeEvent.h"
#include "IAPIBoxMoleculeCountEvent.h"
#include "IAPIBoxMoleculeIndexEvent.h"

namespace molesimAPI
{

    class IAPIBoxListener {

        public:
            /**
              * Method called by box event manager when an atom is added to
              * a box.
              * @param e Box event containing event information.
              */
            virtual void boxAtomAdded(IAPIBoxAtomEvent *e) = 0;
            /**
              * Method called by box event manager when an atom is removed
              * from a box.
              * @param e Box event containing event information.
              */
            virtual void boxAtomRemoved(IAPIBoxAtomEvent *e) = 0;
            /**
              * Method called by box event manager when a molecule is added
              * to a box.
              * @param e Box event containing event information.
              */
            virtual void boxMoleculeAdded(IAPIBoxMoleculeEvent *e) = 0;
            /**
              * Method called by box event manager when a molecule is removed
              * from a box.
              * @param e Box event containing event information.
              */
            virtual void boxMoleculeRemoved(IAPIBoxMoleculeEvent *e) = 0;
            virtual void boxGlobalAtomLeafIndexChanged(IAPIBoxIndexEvent *e) = 0;
            /**
              * Method called by box event manager when an atom's index
              * within the box has changed.
              * @param e Box event containing event information.
              */
            virtual void boxGlobalAtomIndexChanged(IAPIBoxIndexEvent *e) = 0;
            /**
              * Method called by box event manager when an atom's lef index
              * within the box has changed.
              * @param e Box event containing event information.
              */
            virtual void boxAtomLeafIndexChanged(IAPIBoxAtomIndexEvent *e) = 0;
            /**
              * Method called by box event manager when an molecule's index
              * within the box has changed.
              * @param e Box event containing event information.
              */
            virtual void boxMoleculeIndexChanged(IAPIBoxMoleculeIndexEvent *e) = 0;
            /**
              * Method called by box event manager when molecules are added
              * to a box.
              * @param e Box event containing event information.
              */
            virtual void boxNumberMolecules(IAPIBoxMoleculeCountEvent *e) = 0;

    };
}
#endif
