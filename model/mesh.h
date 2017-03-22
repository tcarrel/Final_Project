/**
 * \file mesh.h
 * \author Thomas R. Carrel
 *
 * \brief Mesh class declaration.
 */


#include<GL/glew.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_opengl.h>

#include<GL/gl.h>

#include<glm/glm.hpp>

#ifndef  _MESH_H_
# define _MESH_H_

# include<string>

# include "vertex_array.h"
# include "SG_except.h"

# include "../constants.h"

//# define DEBUG_MESH

class Shader;
namespace App
{
    class Window;
};




namespace Model
{
    namespace OBJ
    {
        class OBJ_File;
    }

    /**
     * Manages mesh data and calls draw functions.
     */
    class Mesh
    {
        public:

            Mesh( const std::string&, GLenum );
            ~Mesh( void );

            void set_shader( Shader* );

            void draw( Shader* prog, glm::mat4* vp, bool draw )
                throw( Scene_Graph_Exception );

            void add_child( Mesh* );
            void set_size( const GLfloat&, const GLfloat& );
            void done( void );

            /** Return the address of the matrix array.
             */
            Vertex_Array* get_array( void )
            { return vertices_; }

            inline bool is_ready( void ){ return !vertices_; }
            inline std::string name( void ){ return name_; }

            void print_info( void );

        private:

            void print_info( std::string );
            void init_gpu_buffers( void );

            GLboolean dirty_;

            Vertex_Array* vertices_; ///< Array of vertex data.
            GLboolean verts_sent_to_gpu_; ///< true if vertices were sent to the
                                          ///< gpu, this mean our local vertex
                                          ///< array is no longer need and can,
                                          ///< therefore, be deleted.
            GLuint  qty_; ///< Number of vertices in the vertex array.

            const GLenum  mode_; ///< The drawing mode for this mesh.

            GLuint  vbo_; ///< Vertex Buffer Object.
            GLuint  vao_; ///< Vertex Array Object.

            Shader* shader_; ///< The "normal" shader program that this mesh is
                             ///< to be rendered with.  For "special" rending a
                             ///< different shader program can be passed in with
                             ///< the draw call.

            /** \todo Additional fields for texture info.
             * Some texture info may need to be passed with each draw call.
             */

            static GLuint           curr_vao_;

            GLfloat                 size_;

            GLuint                  child_qty_;
            Mesh**                  children_;

            const std::string       name_;
    };

} //Model namespace.

#endif
