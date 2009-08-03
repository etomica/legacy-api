/*
 *  GlotzillaSpring.h
 *  API Glue
 *
 */

#ifndef GLOTZ_SPRING_WRAPPER_H
#define GLOTZ_SPRING_WRAPPER_H

#include "IAPIPotential.h"

using namespace molesimAPI;

namespace glotzwrappers
{

    /**
      * GlotzillaSpring is a class representing a spring.  The class is used
      * as a superclass for springs of a specific type.  The class holds a
      * spring constant and extent.
      */
    class GlotzillaSpring : public virtual IAPIPotential {

        public:
            /**
              * Create an instance of a spring with default spring (0.7) and
              * default extent (0.5).
              */
            GlotzillaSpring();
            /**
              * Create an instance of a spring with the given spring and
              * given extent.
              * @param spring Spring property for the spring being created.
              * @param extent Extent property for the spring being created.
              */
            GlotzillaSpring(double spring, double extent);

            // API Compliance
            double getRange();
            double energy(IAPIAtomList *as);
            int nBody();
            void setBox(IAPIBox *box);

            // Non-api Methods
            void setSpringConstant(double spring);
            void setTargetExtent(double extent);
            double getSpringConstant();
            double getTargetExtent();

        private:
            double mSpring;
            double mExtent;

    };
}
#endif
