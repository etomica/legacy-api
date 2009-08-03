/*
 *  GlotzillaIntegratorListener.cpp
 *  API Glue
 *
 */


#include "GlotzillaIntegratorListener.h"

namespace glotzwrappers
{

    GlotzillaIntegratorListener::GlotzillaIntegratorListener(IAPIIntegratorListener *listener) {
        mListener = listener;
    }
	
    /*
     * integratorInitialized()
     */
    void GlotzillaIntegratorListener::integratorInitialized(IAPIIntegratorEvent *event) {
        mListener->integratorInitialized(event);
    }

    /*
     * integratorStepStarted()
     */
    void GlotzillaIntegratorListener::integratorStepStarted(IAPIIntegratorEvent *event) {
        mListener->integratorStepStarted(event);
    }

    /*
     * integratorStepFinished()
     */
    void GlotzillaIntegratorListener::integratorStepFinished(IAPIIntegratorEvent *event) {
        mListener->integratorStepFinished(event);
    }

    /*
     * ApplyPreMovePreForce()
     */
    void GlotzillaIntegratorListener::ApplyPreMovePreForce() {
        integratorStepStarted(NULL);
    }

    /*
     * ApplyPostMovePostForce()
     */
    void GlotzillaIntegratorListener::ApplyPostMovePostForce() {
        integratorStepFinished(NULL);
    }

}
