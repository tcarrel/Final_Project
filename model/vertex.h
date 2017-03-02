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
        glm::vec4 color; ///< Vertex color, temporary.

        /* To be re-included later.
        glm::vec2 texture_coords;
        glm::vec2 phong_coord;
        */


        /** Ctor, inits vertex with a vec3 as input.
         * \param p The coordinates of the vertex.
         * \param c The rgba-color of the vertex.
         */
        Vertex( const glm::vec3& p, const glm::vec4& c ) : pos(p), color(c) {}

        /** Ctor, inits vertex with three floating point numbers.
         * \param x The x-coordinate.
         * \param y The y-coordinate.
         * \param z The z-coordinate.
         * \param r The red color value.
         * \param g The green color value.
         * \param b The blue color value.
         * \param a The alpha color value.
         */
        Vertex(
                float x,
                float y,
                float z,

                float r,
                float g,
                float b,
                float a
                ) :
            pos( glm::vec3( x, y, z ) ),
            color( glm::vec4( r, g, b, a ) )
        {}

        /** Generic ctor, inits the vertex to (0, 0, 0).
         */
        Vertex( void ) :
            Vertex( 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f )
        {}
    };

} //Model namespace.


#endif /* VERTEX_H */
