/**
 * \file GLSL_except.h
 * \author David Wolff
 * 
 * \brief Taken from the book "OpenGL 4 SHading Language Cookbook"
 * by David Wolff.  This file defines a class for handling errors from the
 * compilation of shader programs.*
 */

#include<string>
#include<stdexcept>

#ifndef  _GLSL_EXCEPT_H_
# define _GLSL_EXCEPT_H_



/**  A custom exception class for dealing with shader compilation errors.
 */
class GLSL_Program_Exception : public std::runtime_error
{
    public:
        /** Ctor.
         * \param msg The message related to the error.
         */
        GLSL_Program_Exception( const string& msg ) :
            std::runtime_error( "\033[1;31;40mEXCEPTION!!\033[0m " + msg ) {};
};

#endif
