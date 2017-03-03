/**
 * \file OBJ_except.cpp
 * \author Thomas R. Carrel
 * 
 * \brief The definition of the custom OBJ exception class.
 */

#include "OBJ_except.h"

namespace Model
{

    namespace OBJ
    {

        /** Ctor.
         * \param msg The message related to the error.
         */
        OBJ_Exception::OBJ_Exception( const std::string& msg ) :
            std::runtime_error( "\033[1;31;40mOBJ LOADER EXCEPTION!!\033[0m " + msg )
        {}

    } //OBJ namespace.

} //Model namespace.
