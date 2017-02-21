/**
 * \file vertex.h
 * \author Thomas R. Carrel
 *
 * \brief Declares the format of Vertex data.
 */


#ifndef  VERTEX_H
# define VERTEX_H

#include<initializer_list>

#include<GL/gl.h>
#include<glm/glm.hpp>

namespace Model
{

    /** Struct for storing vertex coordinates.
    */
    struct Vertex
    {
        glm::vec3 pos; ///< The coordinate of the vertex.

        /* To be re-included later.
        glm::vec2 texture_coords;
        glm::vec2 phong_coord;
        */


        /** Ctor, inits vertex with a vec3 as input.
         * \param p The coordinates of the vertex.
         */
        Vertex( const glm::vec3& p ) : pos(p) {}

        /** Ctor, inits vertex with three floating point numbers.
         * \param x The x-coordinate.
         * \param y The y-coordinate.
         * \param z The z-coordinate.
         */
        Vertex( float x, float y, float z ) :
            pos( glm::vec3( x, y, z ) )
        {}

        /** Generic ctor, inits the vertex to (0, 0, 0).
         */
        Vertex( void ) :
            Vertex( 0.0f, 0.0f, 0.0f )
        {}
    };

} //Model namespace.


#endif /* VERTEX_H */
