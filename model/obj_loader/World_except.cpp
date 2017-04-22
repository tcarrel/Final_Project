/**
 * \file OBJ_except.cpp
 * \author Thomas R. Carrel
 * 
 * \brief The definition of the custom OBJ exception class.
 */

#include "World_except.h"

namespace Model
{

    namespace OBJ
    {

        /** Ctor.
         * \param msg The message related to the error.
         */
        World_Exception::World_Exception( const std::string& msg ) :
            std::runtime_error(
                    "\033[1;31;40mLevel file Error!!\033[0m\n\t"
                    + msg
                    + "\n"
                    )
        {}

    } //OBJ namespace.

} //Model namespace.
