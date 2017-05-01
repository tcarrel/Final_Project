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
    class Skybox;

    /**
     * Manages mesh data and calls draw functions.
     */
    class Mesh
    {
        public:

            Mesh( const string&, GLenum );

            void set_shader( Shader* );
            void set_reflect( Shader*, Skybox* );
            void set_refract( Shader*, Skybox*, const GLfloat& );
            void set_fresnel( Shader*, Skybox*, const GLfloat&, const GLfloat& );

            void draw(
                    const glm::mat4&,
                    const glm::mat4&,
                    const glm::mat4&,
                    const glm::vec3& )
                throw( Scene_Graph_Exception );

            void render( void );

            void add_child( Mesh* );
            void set_size( const GLfloat&, const GLfloat& );
            void done( void );

            void bind_vao( void );

            /** Return the address of the matrix array.
            */
            Vertex_Array* get_array( void )
            { return vertices_; }

            inline bool     is_ready( void ){ return !vertices_; }
            inline string   name( void ){ return name_; }

            void print_info( void );

            Mesh* get_ptr( void );
            bool delete_this( void );

        private:
            /** Array of vertex data.
            */
            Vertex_Array*   vertices_; 

            /** true if vertices were sent to the gpu, this mean our local
             * vertex array is no longer need and can, therefore, be deleted.
             */
            GLboolean       verts_sent_to_gpu_;

            /* Number of vertices in the vertex array.
             */
            GLuint          qty_; 
            /** The drawing mode for this mesh.
             */
            const GLenum    mode_; 
            /** Vertex Buffer Object.
             */
            GLuint          vbo_; 
            /** Vertex Array Object.
             */
            GLuint          vao_; 
            /** The "normal" shader program that this mesh is to be rendered
             * with.  For "special" rending a different shader program can be
             * passed in with the draw call.
             */
            Shader*         shader_; 
            /** Stores the current vao, this will allow for some optimization
             * with instanced rendering and later multi-threaded methods.
             */
            static GLuint   curr_vao_;
            /**
             */
            GLfloat         original_scale_;
            /** Used to resize the mesh to its final intended size, of course,
             * later this will need to be able to modified during updates for
             * various animations and other creative purposes..
             */
            GLfloat         scale_factor_;
            /** As some obj files  are composed of multiple seperate meshes,
             * "child" meshes will need to be stored within this mesh.  This
             * member stores the number of additional meshes this within this
             * object.  The entire mesh and its children can only be
             * transformed together as one unit.
             */
            GLuint          child_qty_;
            /** An array of pointers to child meshes.  NULL, if there are no
             * children.  As the number of children is unlikely to every be
             * very large, the method to add children adds dynamically resizes
             * the array one entry at a time, keeping the size minimal.  This
             * does increase the loading times, but not by an appreciable
             * amount.
             */
            Mesh**          children_;
            /** A unique identifier for this specific mesh.  Aside from
             * debugging and identifying models, its existance allows for
             * instanced rendering and eliminates the need to reload models if
             * they are still in memory.
             */
            const string    name_;
            /** Tracks the number of this instance of mesh currently in use.
             */
            GLuint          qty_in_use_;

#  ifdef DEBUG
            bool            draw_message_shown_;
#  endif
            bool            is_reflective_;
            bool            is_refractive_;
            Skybox*         skybox_;
            GLfloat         refractivity_ratio_;
            GLfloat         r_0_;

            /** See the Shader dtor for why it is necessary this be private.
             */
            ~Mesh( void );
            void print_info( string );
            void init_gpu_buffers( void );

            void regular_draw(
                    const glm::mat4&,
                    const glm::mat4&,
                    const glm::mat4&,
                    bool );
            void reflect_draw(
                    const glm::mat4&,
                    const glm::mat4&,
                    const glm::mat4&,
                    const glm::vec3&,
                    bool
                    );
            void transparent_draw(
                    const glm::mat4&,
                    const glm::mat4&,
                    const glm::mat4&,
                    const glm::vec3&,
                    bool );
            void fresnel_draw(
                    const glm::mat4&,
                    const glm::mat4&,
                    const glm::mat4&,
                    const glm::vec3&,
                    bool );
    };

} //Model namespace.

#endif
