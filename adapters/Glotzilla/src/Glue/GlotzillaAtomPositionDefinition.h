/*
 *  GlotzillaAtomPositionDefinition.h
 *  API Glue
 *
 */

#ifndef GLOTZ_ATOMPOSDEF_WRAPPER_H
#define GLOTZ_ATOMPOSDEF_WRAPPER_H

#include "GlotzillaInterfaceAtomPositionDefinition.h"
#include "IAPIMolecule.h"
#include "IAPIVector.h"

using namespace molesimAPI;

namespace glotzwrappers
{

    /**
      * GlotzillaAtomPositionDefinition has no practical application outside
      * of the Glotzilla API glue layer.  It is necessary only for a class
      * to hold method(s) generated by parsers used to create a java proxy
      * class layer.
      * @todo This class should be removed.
      */
    class GlotzillaAtomPositionDefinition : public virtual GlotzillaInterfaceAtomPositionDefinition {

        public:			

            // API Compliance
            IAPIVector *position(IAPIMolecule *atom) {};


    };
}
#endif