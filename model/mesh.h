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
using std::string;

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

            Mesh( const string&, GLenum );
            ~Mesh( void );

            void set_shader( Shader* );

            void draw( const glm::mat4& ) throw( Scene_Graph_Exception );

            //void update();

            void add_child( Mesh* );
            void set_size( const GLfloat&, const GLfloat& );
            void done( void );

            /** Return the address of the matrix array.
             */
            Vertex_Array* get_array( void )
            { return vertices_; }

            inline bool     is_ready( void ){ return !vertices_; }
            inline string   name( void ){ return name_; }

            void print_info( void );

        private:

            void print_info( string );
            void init_gpu_buffers( void );

            Vertex_Array*   vertices_; ///< Array of vertex data.

            GLboolean       verts_sent_to_gpu_; ///< true if vertices were sent
                                                ///<to the gpu, this mean our
                                                ///< local vertex array is no
                                                ///< longer need and can,
                                                ///< therefore, be deleted.

            GLuint          qty_; ///< Number of vertices in the vertex array.
            const GLenum    mode_; ///< The drawing mode for this mesh.
            GLuint          vbo_; ///< Vertex Buffer Object.
            GLuint          vao_; ///< Vertex Array Object.

            Shader*         shader_; ///< The "normal" shader program that this
                                     ///< mesh is to be rendered with.  For
                                     ///< "special" rending a different shader
                                     ///< program can be passed in with the
                                     ///< draw call.

            static GLuint   curr_vao_; ///< Stores the current vao, this will
                                       ///< allow for some optimization with
                                       ///< instanced rendering and later
                                       ///< multi-threaded methods.

            GLfloat         scale_factor_; ///< Used to resize the mesh to its
                                           ///< final intended size, of course,
                                           ///< later this will need to be able
                                           ///< to modified during updates for
                                           ///< various animations and other
                                           ///< creative purposes..

            GLuint          child_qty_; ///< As some obj files  are composed of
                                        ///< multiple seperate meshes, "child"
                                        ///< meshes will need to be stored
                                        ///< within this mesh.  This member
                                        ///< stores the number of additional
                                        ///< meshes this within this object.
                                        ///< The entire mesh and its children
                                        ///< can only be transformed together
                                        ///< as one unit.

            Mesh**          children_; ///< An array of pointers to child
                                       ///< meshes.  NULL, if there are no
                                       ///< children.  As the number of
                                       ///< children is unlikely to every be
                                       ///< very large, the method to add
                                       ///< children adds dynamically resizes
                                       ///< the array one entry at a time,
                                       ///< keeping the size minimal.  This
                                       ///< does increase the loading times,
                                       ///< but not by an appreciable amount.

            const string    name_; ///< A unique identifier for this specific
                                   ///< mesh.  Aside from debugging and
                                   ///< identifying models, its existance
                                   ///< allows for instanced rendering and
                                   ///< eliminates the need to reload models if
                                   ///< they are still in memory.
    };

} //Model namespace.

#endif
