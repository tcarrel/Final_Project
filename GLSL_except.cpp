/**
 * \file GLSL_except.cpp
 * \author Thomas R. Carrel
 * 
 * \brief The definition of the custom GLSL exception class.
 */

#include "GLSL_except.h"

/** Ctor.
 * \param msg The message related to the error.
 */
GLSL_Program_Exception::GLSL_Program_Exception( const std::string& msg ) :
    std::runtime_error(
            "\033[1;31;40mGLSL EXCEPTION :\033[0m\n\t"
            + msg
            + "\n"
            )
{}

