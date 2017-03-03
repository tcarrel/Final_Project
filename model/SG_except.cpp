/**
 * \file SG_except.cpp
 * \author Thomas R. Carrel
 * 
 * \brief The definition of the custom SG exception class.
 */

#include "SG_except.h"

namespace Model
{

    /** Ctor.
     * \param msg The message related to the error.
     */
    Scene_Graph_Exception::Scene_Graph_Exception( const std::string& msg ) :
        std::runtime_error( "\033[1;31;40mSG EXCEPTION!!\033[0m\n\t" + msg + "\n" )
    {}

} //Model namespace.
