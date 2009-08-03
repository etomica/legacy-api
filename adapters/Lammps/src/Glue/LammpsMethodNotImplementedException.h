/*
 *  LammpsMethodNotImplementedException.h
 *  API Glue
 *
 */

#ifndef LAMMPS_EXCEPTION_METHODNOTIMPLEMENTED_WRAPPER_H
#define LAMMPS_EXCEPTION_METHODNOTIMPLEMENTED_WRAPPER_H

#include <exception>

namespace lammpswrappers
{

    class LammpsMethodNotImplementedException : public std::exception {

        public:

            LammpsMethodNotImplementedException(char *msg);

            const char *what() const throw();

        private:
            char *mMessage;

    };
}
#endif
