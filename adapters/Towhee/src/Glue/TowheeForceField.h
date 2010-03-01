/*
 *  TowheeForceField.h
 *  API Glue
 *
 */

#ifndef TOWHEE_FORCE_FIELD_WRAPPER_H
#define TOWHEE_FORCE_FIELD_WRAPPER_H

namespace towheewrappers
{

    class TowheeForceField {

        public:
            TowheeForceField(char *file, char *name);

            char *getForcefieldName();
            char *getFileName();
            void setup();

        private:
            char *mFilename;
            char *mName;

    };
}
#endif
