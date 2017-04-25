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
        /** Position
         */
        glm::vec3 pos;
        /** Color
         */
        glm::vec4 color;
        /** Normal vector.
         */
        glm::vec3 normal;


        /** Ctor.
         * @param p The vertex position.
         * @param c The vertex color, this will later be change to the vertex
         * normal.
         * @param n The normal vector.
         */
        Vertex( const glm::vec3& p, const glm::vec4& c, const glm::vec3& n ) :
            pos(p),
            color(c),
            normal(glm::normalize(n))
        {}

        /** Ctor.
         * @param p The vertex position.
         * @param c The vertex color, this will later be change to the vertex
         * normal.
         * @param n The normal vector.
         */
        Vertex( const glm::vec3& p, const glm::vec3& c, const glm::vec3& n ) :
            pos(p),
            color( glm::vec4( c.x, c.y, c.z, 1.0f ) ),
            normal(glm::normalize(n))
        {}

        /** Ctor, inits vertex with three floating point numbers.
         * @param x The x-coordinate.
         * @param y The y-coordinate.
         * @param z The z-coordinate.
         *
         * @param r The red color value.
         * @param g The green color value.
         * @param b The blue color value.
         * @param a The alpha color value.
         *
         * @param nx The x component of the normal vector.
         * @param ny The y component of the normal vector.
         * @param nz The z component of the normal vector.
         */
        Vertex(
                float x,  float y,  float z,           //Position
                float r,  float g,  float b,  float a, //Color
                float nx, float ny, float nz           //Normal
                ) :
            pos( glm::vec3( x, y, z ) ),
            color( glm::vec4( r, g, b, a ) ),
            normal( glm::normalize( glm::vec3( nx, ny, nz ) ) )
        {}

        /** Generic ctor, inits the vertex to (1, 0, 0, 0, 0, 1, 0, 1, 0).
         */
        Vertex( void ) :
            Vertex( 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f )
        {}


        /** Copy constructor.
         * @param b The Vertex to be copied.
         */
        Vertex( const Vertex& b )
        {
            this->pos   =   b.pos;
            this->color =   b.color;
            this->normal=   b.normal;
        }


        /** Assignment operator.
         * @param rhs The Vertex to be assigned from.
         */
        const Vertex& operator=( const Vertex& rhs )
        {
            this->pos   =   rhs.pos;
            this->color =   rhs.color;
            this->normal=   rhs.normal;
            return *this;
        }
    };

} //Model namespace.


#endif /* VERTEX_H */
