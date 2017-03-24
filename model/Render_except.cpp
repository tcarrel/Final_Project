/**
 * \file Render_except.cpp
 * \author Thomas R. Carrel
 * 
 * \brief The definition of the custom Render exception class.
 */

#include "Render_except.h"

namespace Model
{

    /** Ctor.
     * \param msg The message related to the error.
     */
    Render_Exception::Render_Exception( const std::string& msg ) :
        std::runtime_error(
                "\033[1;31;40mRendering EXCEPTION!!\033[0m\n\t"
                + msg
                + "\n"
                )
    {}

} //Model namespace.
