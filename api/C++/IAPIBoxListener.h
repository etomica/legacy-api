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
            virtual void boxAtomAdded(IAPIBoxAtomEvent *e) = 0;
            virtual void boxAtomRemoved(IAPIBoxAtomEvent *e) = 0;
            virtual void boxMoleculeAdded(IAPIBoxMoleculeEvent *e) = 0;
            virtual void boxMoleculeRemoved(IAPIBoxMoleculeEvent *e) = 0;
            virtual void boxGlobalAtomLeafIndexChanged(IAPIBoxIndexEvent *e) = 0;
            virtual void boxGlobalAtomIndexChanged(IAPIBoxIndexEvent *e) = 0;
            virtual void boxAtomLeafIndexChanged(IAPIBoxAtomIndexEvent *e) = 0;
            virtual void boxMoleculeIndexChanged(IAPIBoxMoleculeIndexEvent *e) = 0;
            virtual void boxNumberMolecules(IAPIBoxMoleculeCountEvent *e) = 0;

    };
}
#endif
