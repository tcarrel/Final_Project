/**
 * \file OBJ_except.h
 * \author Thomas R. Carrel
 * 
 * \brief Declaration of custom  World_exception class.
 * Based on the one used for the shader compiler.
 */

#include<string>
#include<stdexcept>

#ifndef  _WORLD_LOADER_EXCEPT_H_
# define _WORLD_LOADER_EXCEPT_H_


namespace Model
{

    namespace OBJ
    {

        /**  A custom exception class for dealing with world loading.
         */
        class World_Exception : public std::runtime_error
        {
            public:
                /** Ctor.
                 * \param msg The message related to the error.
                 */
                World_Exception( const std::string& );
        };

    } //OBJ namespace.

} //Model namespace.

#endif
