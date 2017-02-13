/**
 * \file mesh.h
 * \author Thomas R. Carrel
 */


#include<GL/glew.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_opengl.h>

#include<GL/glu.h>
#include<GL/freeglut.h>

#ifndef  _MESH_H_
# define _MESH_H_

#include "vertex.h"

class Shader;



/**
 * Manages mesh data and calls draw functions.
 */
class Mesh
{
    public:
        Mesh( void );
        Mesh( GLchar* );
        Mesh( Vertex*, GLuint );
        ~Mesh( void );

        void set_shader( Shader* );

        const GLuint& indices_per_vertex( void ){ return ipv_; }

        void draw( Shader* );
    private:
        Vertex* vertices_; ///< Array of vertex data.
        GLboolean verts_sent_to_gpu_; ///< true if vertices were sent to the
                                      ///< gpu, this mean our local vertex
                                      ///< array is no longer need and can,
                                      ///< therefore, be deleted.
        GLuint qty_; ///< Number of vertices in the vertex array.

        const GLuint ipv_; ///< Indices Per Vertex.
                           ///< ipv_ * qty_ == Length of vertex array.

        Shader* shader_; ///< The "normal" shader program that this mesh is to
                         ///< be rendered with.  For "special" rending a
                         ///< different shader program can be passed in with
                         ///< the draw call.

        /** \todo Additional fields for texture info.
         * Some texture info may need to be passed with each draw call.
         */
};

#endif
