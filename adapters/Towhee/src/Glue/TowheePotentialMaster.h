/*
 *  TowheePotentialMaster.h
 *  API Glue
 *
 *
 */

#ifndef TOWHEE_POTENTIAL_MASTER_WRAPPER_H
#define TOWHEE_POTENTIAL_MASTER_WRAPPER_H

#include <vector>

#include "TowheeForceField.h"
#include "IAPIAtomType.h"

namespace towheewrappers
{

    class TowheePotentialMaster {

        public:

            // Non-API
            void addForceField(TowheeForceField *ff);
            int getForceFieldCount();
            TowheeForceField *getForceField(int idx);

        private:
            std::vector<TowheeForceField *>mForceField;
    };
}
#endif
