/**
 * \file OBJ_except.h
 * \author Thomas R. Carrel
 * 
 * \brief Declaration of custom OBJ loader exception class.
 * Based on the one used for the shader compiler.
 */

#include<string>
#include<stdexcept>

#ifndef  _SCENE_GRAPH_EXCEPT_H_
# define _SCENE_GRAPH_EXCEPT_H_


namespace Model
{

    namespace OBJ
    {

        /**  A custom exception class for dealing with scene graph
         * creation errors.
         */
        class OBJ_Exception : public std::runtime_error
        {
            public:
                /** Ctor.
                 * \param msg The message related to the error.
                 */
                OBJ_Exception( const std::string& );
        };

    } //OBJ namespace.

} //Model namespace.

#endif
