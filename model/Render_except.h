/**
 * \file Render_except.h
 * \author Thomas R. Carrel
 * 
 * \brief Declaration of custom Render exception class.
 * Based on the one used for the shader compiler.
 */

#include<string>
#include<stdexcept>

#ifndef  _RENDER_EXCEPT_H_
# define _RENDER_EXCEPT_H_


namespace Model
{

    /**  A custom exception class for dealing with scene graph
     * creation errors.
    */
    class Render_Exception : public std::runtime_error
    {
        public:
            /** Ctor.
             * \param msg The message related to the error.
             */
            Render_Exception( const std::string& );
    };

} //Model namespace.

#endif
