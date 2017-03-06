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
//        glm::vec2 uv;  ///< Texture coordinates.
        glm::vec4 color; ///< Vertex color, temporary. Later, normals.

        /* To be re-included later.
        glm::vec2 texture_coords;
        glm::vec2 phong_coord;
        */


        /* Ctor, inits vertex with a vec3 as input.
         * \param p The coordinates of the vertex.
         * \param u The uv-texture coordinates.
         * \param c The rgba-color of the vertex.
         */
        /*
        Vertex(
                const glm::vec3& p,
                const glm::vec2& u,
                const glm::vec4& c
                ) 
            : pos(p), uv(u), color(c) {}
            */



        /** Temporary ctor for during development.
         * \param p The vertex position.
         * \param c The vertex color.
         */
        Vertex( const glm::vec3& p, const glm::vec4& c ) :
            pos(p), color(c)
        {}

        /** Ctor.
         * \param p The vertex position.
         * \param c The vertex color, this will later be change to the vertex
         * normal.
         */
        Vertex( const glm::vec3& p, const glm::vec3& c ) :
            pos(p), color( glm::vec4( c.x, c.y, c.z, 1.0f ) )
        {}


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


        /** Copy constructor.
         * \param b The Vertex to be copied.
         */
        Vertex( const Vertex& b )
        {
            this->pos   =   b.pos;
            this->color =   b.color;
        }


        /** Assignment operator.
         * \param rhs The Vertex to be assigned from.
         */
        Vertex& operator=( const Vertex& rhs )
        {
            this->pos   =   rhs.pos;
            this->color =   rhs.color;
            return *this;
        }
    };

} //Model namespace.


#endif /* VERTEX_H */
