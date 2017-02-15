/**
 * \file vertex.h
 * \author Thomas R. Carrel
 */


#ifndef  VERTEX_H
# define VERTEX_H

#include<initializer_list>

#include<GL/gl.h>

/** Struct for storing vertex coordinates.
 */
struct Vertex
{
    GLfloat x; ///< x-coordinate.
    GLfloat y; ///< y-coordinate.
    GLfloat z; ///< z-coordinate.
    /*
       GLfloat u; ///< Texture coordinate, u.
       GLfloat v; ///< Texture coordinate, v
       */
};

#endif /* VERTEX_H */
