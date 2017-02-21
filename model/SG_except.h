/**
 * \file SG_except.h
 * \author Thomas R. Carrel
 * 
 * \brief Declaration of custom Scene Graph exception class.
 * Based on the one used for the shader compiler.
 */

#include<string>
#include<stdexcept>

#ifndef  _SCENE_GRAPH_EXCEPT_H_
# define _SCENE_GRAPH_EXCEPT_H_


namespace Model
{

    /**  A custom exception class for dealing with scene graph
     * creation errors.
    */
    class Scene_Graph_Exception : public std::runtime_error
    {
        public:
            /** Ctor.
             * \param msg The message related to the error.
             */
            Scene_Graph_Exception( const std::string& );
    };

} //Model namespace.

#endif
