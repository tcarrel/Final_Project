/**
 * \file mesh.cpp
 * \author Thomas R. Carrel
 *
 * \brief Definitions for Mesh class.
 */


#include "mesh.h"
//#include "vertex_array.h"

#include "../shader_program.h"
#include "../app/window.h"
#include "../helper_functions.h"
#include "../colors.h"

#include<stdio.h>
#include<glm/ext.hpp>


namespace Model
{

    GLuint Mesh::curr_vao_ = UINT_MAX;



    /**
     * Ctor.
     * \param w A reference to the window.  Needed for swaping buffers.
     * \param m The rendering mode to be used for this mesh.
     */
    Mesh::Mesh( App::Window* w, GLenum m = GL_TRIANGLES ) :
        dirty_( true ),
        verts_sent_to_gpu_( false ),
        mode_( m ),
        vbo_( 0 ),
        vao_( 0 )
    {
#ifdef DEBUG
        fprintf(
                stderr,
                "Vertex Size\t:\t%li\n",
                sizeof(Vertex)
               );
#endif

        /** Hard coded cube mesh
         * Delete later.
         * vertex coordinates borrowed from
         * http://www.opengl-tutorial.org/beginners-tutorials/tutorial-4-a-colored-cube/
         */


        //1
        vertices_.add( Vertex( glm::vec3( -1.0f,-1.0f,-1.0f ), to_vec_color( Color::random_color() | 0xff ) ) );
        vertices_.add( Vertex( glm::vec3( -1.0f,-1.0f, 1.0f ), to_vec_color( Color::random_color() | 0xff ) ) );
        vertices_.add( Vertex( glm::vec3( -1.0f, 1.0f, 1.0f ), to_vec_color( Color::random_color() | 0xff ) ) );

        //2
        vertices_.add( Vertex( glm::vec3( 1.0f, 1.0f,-1.0f ), to_vec_color(  Color::random_color() | 0xff) ) );
        vertices_.add( Vertex( glm::vec3( -1.0f,-1.0f,-1.0f ), to_vec_color( Color::random_color() | 0xff ) ) );
        vertices_.add( Vertex( glm::vec3( -1.0f, 1.0f,-1.0f ), to_vec_color( Color::random_color() | 0xff ) ) );

        //3
        vertices_.add( Vertex( glm::vec3( 1.0f,-1.0f, 1.0f ), to_vec_color(  Color::random_color() | 0xff ) ) );
        vertices_.add( Vertex( glm::vec3( -1.0f,-1.0f,-1.0f ), to_vec_color( Color::random_color() | 0xff ) ) );
        vertices_.add( Vertex( glm::vec3( 1.0f,-1.0f,-1.0f ), to_vec_color(  Color::random_color() | 0xff ) ) );

        //4
        vertices_.add( Vertex( glm::vec3( 1.0f, 1.0f,-1.0f ), to_vec_color(  Color::random_color() | 0xff ) ) );
        vertices_.add( Vertex( glm::vec3( 1.0f,-1.0f,-1.0f ), to_vec_color(  Color::random_color() | 0xff ) ) );
        vertices_.add( Vertex( glm::vec3( -1.0f,-1.0f,-1.0f ), to_vec_color( Color::random_color() | 0xff ) ) );

        //5
        vertices_.add( Vertex( glm::vec3( -1.0f,-1.0f,-1.0f ), to_vec_color( Color::random_color() | 0xff ) ) );
        vertices_.add( Vertex( glm::vec3( -1.0f, 1.0f, 1.0f ), to_vec_color( Color::random_color() | 0xff ) ) );
        vertices_.add( Vertex( glm::vec3( -1.0f, 1.0f,-1.0f ), to_vec_color( Color::random_color() | 0xff ) ) );

        //6
        vertices_.add( Vertex( glm::vec3( 1.0f,-1.0f, 1.0f ), to_vec_color(  Color::random_color() | 0xff ) ) );
        vertices_.add( Vertex( glm::vec3( -1.0f,-1.0f, 1.0f ), to_vec_color( Color::random_color() | 0xff ) ) );
        vertices_.add( Vertex( glm::vec3( -1.0f,-1.0f,-1.0f ), to_vec_color( Color::random_color() | 0xff ) ) );

        //7
        vertices_.add( Vertex( glm::vec3( -1.0f, 1.0f, 1.0f ), to_vec_color( Color::random_color() | 0xff ) ) );
        vertices_.add( Vertex( glm::vec3( -1.0f,-1.0f, 1.0f ), to_vec_color( Color::random_color() | 0xff ) ) );
        vertices_.add( Vertex( glm::vec3( 1.0f,-1.0f, 1.0f ), to_vec_color(  Color::random_color() | 0xff ) ) );

        //8
        vertices_.add( Vertex( glm::vec3( 1.0f, 1.0f, 1.0f ), to_vec_color( Color::random_color() | 0xff ) ) );
        vertices_.add( Vertex( glm::vec3( 1.0f,-1.0f,-1.0f ), to_vec_color( Color::random_color() | 0xff ) ) );
        vertices_.add( Vertex( glm::vec3( 1.0f, 1.0f,-1.0f ), to_vec_color( Color::random_color() | 0xff ) ) );

        //9
        vertices_.add( Vertex( glm::vec3( 1.0f,-1.0f,-1.0f ), to_vec_color( Color::random_color() | 0xff ) ) );
        vertices_.add( Vertex( glm::vec3( 1.0f, 1.0f, 1.0f ), to_vec_color( Color::random_color() | 0xff ) ) );
        vertices_.add( Vertex( glm::vec3( 1.0f,-1.0f, 1.0f ), to_vec_color( Color::random_color() | 0xff ) ) );

        //10
        vertices_.add( Vertex( glm::vec3( 1.0f, 1.0f, 1.0f ), to_vec_color(  Color::random_color() | 0xff ) ) );
        vertices_.add( Vertex( glm::vec3( 1.0f, 1.0f,-1.0f ), to_vec_color(  Color::random_color() | 0xff ) ) );
        vertices_.add( Vertex( glm::vec3( -1.0f, 1.0f,-1.0f ), to_vec_color( Color::random_color() | 0xff ) ) );

        //11
        vertices_.add( Vertex( glm::vec3( 1.0f, 1.0f, 1.0f ), to_vec_color(  Color::random_color() | 0xff ) ) );
        vertices_.add( Vertex( glm::vec3( -1.0f, 1.0f,-1.0f ), to_vec_color( Color::random_color() | 0xff ) ) );
        vertices_.add( Vertex( glm::vec3( -1.0f, 1.0f, 1.0f ), to_vec_color( Color::random_color() | 0xff ) ) );

        //12
        vertices_.add( Vertex( glm::vec3( 1.0f, 1.0f, 1.0f ), to_vec_color(  Color::random_color() | 0xff ) ) );
        vertices_.add( Vertex( glm::vec3( -1.0f, 1.0f, 1.0f ), to_vec_color( Color::random_color() | 0xff ) ) );
        vertices_.add( Vertex( glm::vec3( 1.0f,-1.0f, 1.0 ), to_vec_color(   Color::random_color() | 0xff ) ) );

        /*
        vertices_.add( Vertex( glm::vec3( -0.5f, -0.5f, 0.0f ) ) );
        vertices_.add( Vertex( glm::vec3(  0.0f,  0.5f, 0.0f ) ) );
        vertices_.add( Vertex( glm::vec3(  0.5f, -0.5f, 0.0f ) ) );
        */

        vertices_.done();

        fprintf( stderr,
                "Position\t[%s]\nColor\t\t[%s]\n\n",
                glm::to_string( vertices_[0].pos ).c_str(),
                glm::to_string( vertices_[0].color ).c_str()
               );


        qty_ = vertices_.size();;

        window_ = w;

        init_gpu_buffers();
    }





    /** Load vertex data from .obj file.
     * \param filename The name of the .obj file to load.
     * \todo this cannot be implented until the recursive descent parser for
     * loading .obj's has been writen.
     *
     * \param w A reference to the window.  Needed for swapping out
     * framebuffers.
     * \param filename Name of the file to load.
     * \param m The rendering mode for this mesh.
     */

    Mesh::Mesh( App::Window* w, GLchar* filename, GLenum m = GL_TRIANGLES ) 
        : mode_( m )
    {
        /// Call the .obj loader, etc.
    }







    /** Mesh dtor.
    */
    Mesh::~Mesh( void )
    {
        /**
         * We cannot delete shaders explicitly as there is no way to easily tell if
         * they are be used in for rendering multiple meshes.  For the time being,
         * we will rely on the OS to clean up after us after program exit.  As the
         * program becomes more mature, we will store a list of all shader program
         * created and create a SIGKILL handler to delete them on exit and no
         * sooner.
         */
        shader_ = NULL;
        window_ = NULL;

        glDeleteVertexArrays( 1, &vao_ );
        glDeleteBuffers( 1, &vbo_ );

        vao_ = vbo_ = UINT_MAX;
    }






    /** For now, this will be responsible for sending all the draw calls to the gpu.
     * Later, this will be responsible only for creating command packets and
     * sending those to the command buffer.
     * \param prog If using a shader other than the 
     * \param vp The view-projection matrix
     */
    void Mesh::draw( Shader* prog, glm::mat4* vp )
        throw( Scene_Graph_Exception )
    {
        Shader* sh = NULL;

        if( prog )
        {
            prog->use_program();
            sh = prog;
        }
        else if( shader_ )
        {
            shader_->use_program();
            sh = shader_;
        }
        else
        {
            throw( Scene_Graph_Exception(
                        "No shader program provided to mesh object.\n" ) );
        }


        if( curr_vao_ != vao_ )
        {
            glBindVertexArray( vao_ );
            curr_vao_ = vao_;
        }

        if( vp )
        {
            sh->set_uniform( "vp", *vp );
        }

        glDrawArrays( mode_, 0, qty_ );
    }




    //void Mesh::





    /**  Set the default shader program to be used when rendering this mesh.
     * \param p A pointer to the Shader object that will be used.
     */
    void Mesh::set_shader( Shader* p )
    {
        shader_ = p;
    }






    void Mesh::init_gpu_buffers( void )
    {
#ifdef DEBUG
        fprintf(
                stderr,
                "Vertex Array:\n"
                "size  =  %i\n",
                vertices_.size()
               );
#endif
        glGenVertexArrays( 1, &vao_ );
        glBindVertexArray( vao_ );

        glGenBuffers( 1, &vbo_ ); 
        glBindBuffer( GL_ARRAY_BUFFER, vbo_ );
        glBufferData(
                GL_ARRAY_BUFFER,
                sizeof(Vertex) * vertices_.size(),
                vertices_.data_addr(),
                GL_STATIC_DRAW
                );

        glEnableVertexAttribArray( 0 );
        glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) 0 );
        glEnableVertexAttribArray( 1 );
        glVertexAttribPointer( 1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) (3 * sizeof(GLfloat)) );
    }

} //Model namespace.

