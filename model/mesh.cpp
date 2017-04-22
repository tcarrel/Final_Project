/**
 * \file mesh.cpp
 * \author Thomas R. Carrel
 *
 * \brief Definitions for Mesh class.
 */


#include "../shader_program.h"
#include "../app/window.h"
#include "../colors.h"

#include "mesh.h"
#include "skybox.h"
#include "vertex.h"

#include<stdio.h>
#include<glm/ext.hpp>

#define GLM_INCLUDED
#include "../helper_functions.h"
#undef GLM_INCLUDED


/** Set to false in order to color vertices using their normal vector,
 * set to true to assign a random color to each vertex.
 */
#define COLOR_RANDOMLY false

namespace Model
{
    GLuint          Mesh::curr_vao_ = 0;

    /**
     * Ctor.
     * @param name Each loaded mesh will be given a unique name that can be
     * used later to identify them.
     * @param m The rendering mode to be used for this mesh.
     */
    Mesh::Mesh( const std::string& name, GLenum m = GL_TRIANGLES ) :
        vertices_( new Vertex_Array ),
        verts_sent_to_gpu_( false ),
        qty_( 0 ),
        mode_( m ),
        vbo_( 0 ),
        vao_( 0 ),
        original_scale_( 1.0f ),
        scale_factor_( 1.0f ),
        child_qty_( 0 ),
        children_( NULL ),
        name_( name ),
        qty_in_use_( 1 ),
        is_reflective_( false ),
        is_refractive_( false ),
        skybox_( NULL ),
        refractivity_ratio_( 1.0f )
    {
#ifdef DEBUG
        draw_message_shown_ = false;
#endif
    }




    void Mesh::done( void )
    {
        if( !verts_sent_to_gpu_ )
        {
            qty_ = vertices_->size();
            init_gpu_buffers();
            verts_sent_to_gpu_ = true;
        }

        for( GLuint i = 0; i < child_qty_; i++ )
        {
            children_[i]->done();
        }
    }




    Mesh* Mesh::get_ptr( void )
    {
        qty_in_use_++;
        return this;
    }





    bool Mesh::delete_this( void )
    {
        --qty_in_use_;
        if( qty_in_use_ > 0 )
        {
            return false;
        }
        delete this;
        return true;
    }





    /** Mesh dtor.
    */
    Mesh::~Mesh( void )
    {
        shader_->delete_this();

        fprintf( stderr, "***\n" );

        glDeleteVertexArrays( 1, &vao_ );
        glDeleteBuffers( 1, &vbo_ );

        vao_ = vbo_ = 0;

        if( child_qty_ > 0 )
        {
            for( GLuint i = 0; i < child_qty_; i++ )
            {
                children_[i]->delete_this();
                children_[i] = NULL;
            }
            delete [] children_;
            children_ = NULL;
            child_qty_ = 0;
        }
    }






    /** For now, this will be responsible for sending all the draw calls to the
     * gpu.  Later, this will be responsible only for creating command packets
     * and sending those to the command buffer.
     * @param m The model matrix.
     * @param v The view matrix.
     * @param p The projection matrix / frustum.
     * @param c The camera position vector.
     */
    void Mesh::draw(
            const glm::mat4& m,
            const glm::mat4& v,
            const glm::mat4& p,
            const glm::vec3& c ) throw( Scene_Graph_Exception )
    {

        if( !shader_ )
        {
            fprintf( stderr, "Name: %s\n", name_.c_str() );
            throw( Scene_Graph_Exception(
                        "No shader program set to mesh.\n" ) );
        }

        shader_->use_program();

        if( is_reflective_ && is_refractive_ )
        {

            return;
        }

        if( is_reflective_ )
        {
            reflect_draw( m, v, p, c, false );
            return;
        }

        if( is_refractive_ )
        {
            transparent_draw( m, v, p, c, false );
            return;
        }

        regular_draw( m, v, p, false );
        return;
    }




    /**  Use normal rendering method.
     * @param m The model matrix.
     * @param v The view matrix.
     * @param p The projection matrix / frustum.
     * @param uniforms_set Have the uniforms been updated yet?
     */
    void Mesh::regular_draw(
            const glm::mat4& m,
            const glm::mat4& v,
            const glm::mat4& p,
            bool  uniforms_set )
    {
        if( !uniforms_set )
        {
            shader_->set_uniform( "model", m );
            shader_->set_uniform( "view", v );
            shader_->set_uniform( "projection", p );
        }

        glBindVertexArray( vao_ );
        glDrawArrays( mode_, 0, qty_ );

        for( GLuint i = 0; i < child_qty_; i++ )
        {
            children_[i]->regular_draw( m, v, p, true );
        }
    }





    /**  Use refractive rendering method.
     * @param m The model matrix.
     * @param v The view matrix.
     * @param p The projection matrix / frustum.
     * @param c The camera position vector.
     * @param uniforms_set Have the uniforms been updated yet?
     */
    void Mesh::transparent_draw(
            const glm::mat4& m,
            const glm::mat4& v,
            const glm::mat4& p,
            const glm::vec3& c,
            bool  uniforms_set )
    {
        if( !uniforms_set )
        {
            shader_->set_uniform( "model", m );
            shader_->set_uniform( "view", v );
            shader_->set_uniform( "proj", p );
            shader_->set_uniform( "cam_pos", c );
            shader_->set_uniform( "refractive_ratio", refractivity_ratio_ );
        }

        glBindVertexArray( vao_ );
        glBindTexture( GL_TEXTURE_CUBE_MAP, skybox_->get_tex_handle() );
        glDrawArrays( mode_, 0, qty_ );

        for( GLuint i = 0; i < child_qty_; i++ )
        {
            children_[i]->transparent_draw( m, v, p, c, true );
        }
    }





    /**  Use reflective rendering method.
     * @param m The model matrix.
     * @param v The view matrix.
     * @param p The projection matrix / frustum.
     * @param c The camera position vector.
     * @param uniforms_set Have the uniforms been updated yet?
     */
    void Mesh::reflect_draw(
            const glm::mat4& m,
            const glm::mat4& v,
            const glm::mat4& p,
            const glm::vec3& c,
            bool  uniforms_set )
    {
        if( !uniforms_set )
        {
            shader_->set_uniform( "model", m );
            shader_->set_uniform( "view", v );
            shader_->set_uniform( "proj", p );
            shader_->set_uniform( "cam_pos", c );
        }

        glBindVertexArray( vao_ );
        glBindTexture( GL_TEXTURE_CUBE_MAP, skybox_->get_tex_handle() );
        glDrawArrays( mode_, 0, qty_ );

        for( GLuint i = 0; i < child_qty_; i++ )
        {
            children_[i]->reflect_draw( m, v, p, c, true );
        }
    }


    /**  Set the default shader program to be used when rendering this mesh.
     * @param p A pointer to the Shader object that will be used.
     */
    void Mesh::set_shader( Shader* p )
    {
        shader_ = p->get_ptr();
        for( GLuint i = 0; i < child_qty_; i++ )
        {
            children_[i]->set_shader(p);
        }
    }





    /**  Set the object as reflective.
     * @param shader Pointer to the shader for reflection.
     * @param skybox Pointer to the skybox.
     */
    void Mesh::set_reflect( Shader* shader, Skybox* skybox )
    {
        if( shader_ )
        {
            shader_->delete_this();
        }
        if( shader_ == shader )
        {
            return;
        }

        fprintf(
                stderr,
                "Mesh %s, render mode set to reflective.\n" ,
                name_.c_str()
               );

        shader_         =   shader->get_ptr();
        skybox_         =   skybox;
        is_reflective_  =   true;
        is_refractive_  =   false;
        for( GLuint i = 0; i < child_qty_; i++ )
        {
            children_[i]->set_reflect( shader, skybox );
        }
    }





    /**  Set the object as refractive.
     * @param shader Pointer to the shader for refraction.
     * @param skybox Pointer to the skybox.
     * @param rr The ratio of refractivity.
     */
    void Mesh::set_refract( Shader* shader, Skybox* skybox, const GLfloat& rr )
    {
        if( shader_ )
        {
            shader_->delete_this();
        }
        if( shader_ == shader )
        {
            return;
        }

        fprintf(
                stderr,
                "Mesh %s, render mode set to reflective.\n" ,
                name_.c_str()
               );

        shader_                 =   shader->get_ptr();
        skybox_                 =   skybox;
        is_refractive_          =   true;
        is_reflective_          =   false;
        refractivity_ratio_     =   rr;

        for( GLuint i = 0; i < child_qty_; i++ )
        {
            children_[i]->set_refract( shader, skybox, rr );
        }
    }





    /**  Sets up gbu buffers and fills them with the appropriate data.
    */
    void Mesh::init_gpu_buffers( void )
    {
#ifdef DEBUG
        fprintf(
                stderr,
                "Vertex Array:\n"
                "size  =  %i\n",
                vertices_->size()
               );
#endif

        if( verts_sent_to_gpu_ )
        {
            return;
        }
        //        vertices_->center();
        vertices_->scale( scale_factor_ );

        fprintf(
                stderr,
                "Vertex size = %li\nvec3 size = %li\nvec4 size = %li\nGLfloat size = %li\n",
                sizeof(Vertex),
                sizeof(glm::vec3),
                sizeof(glm::vec4),
                sizeof(GLfloat) );

        GLsizei stride = sizeof(Vertex);

        glGenVertexArrays( 1, &vao_ );
        glBindVertexArray( vao_ );

        glGenBuffers( 1, &vbo_ ); 
        glBindBuffer( GL_ARRAY_BUFFER, vbo_ );
        glBufferData(
                GL_ARRAY_BUFFER,
                sizeof(Vertex) * vertices_->size(),
                vertices_->data_addr(),
                GL_STATIC_DRAW
                );

        glEnableVertexAttribArray( 0 );
        glVertexAttribPointer(
                0,
                3,
                GL_FLOAT,
                GL_FALSE,
                stride,
                (void*) 0
                );
        glEnableVertexAttribArray( 1 );
        glVertexAttribPointer(
                1,
                4,
                GL_FLOAT,
                GL_FALSE,
                stride,
                (void*) sizeof(glm::vec3)
                );
        glEnableVertexAttribArray( 2 );
        glVertexAttribPointer(
                2,
                3,
                GL_FLOAT,
                GL_FALSE,
                stride,
                (void*) (sizeof(glm::vec3) + sizeof(glm::vec4))
                );

        verts_sent_to_gpu_ = true;
    }






    /** Add a child mesh.
     * @param child The mesh to be added.
     */
    void Mesh::add_child( Mesh* child )
    {
        GLuint old_qty = child_qty_++;
        Mesh** temp = children_;
        children_ = new Mesh*[child_qty_];

        for( GLuint i = 0; i < old_qty; i++ )
        {
            children_[i] = temp[i];
            temp[i] = NULL;
        }
        children_[old_qty] = child->get_ptr();

        delete [] temp;
    }







    void Mesh::set_size( const GLfloat& size, const GLfloat& total )
    {
        scale_factor_ = size / total;

        for( GLuint i = 0; i < child_qty_; i++ )
        {
            children_[i]->set_size( size, total );
        }
    }




    void Mesh::print_info( void )
    {
        std::string spacing = "  ";
        fprintf(
                stdout,
                "Mesh debug output\n"
                "=================\n"
                "%s%s:\n"
                "  %sSize:\t\t%f\n"
                "  %sVertices:\t\t%d\n",
                spacing.c_str(),
                name_.c_str(),
                spacing.c_str(),
                scale_factor_,
                spacing.c_str(),
                vertices_->size()
               );

        for( GLuint i = 0; i < child_qty_; i++ )
        {
            children_[i]->print_info( spacing + "  " );
        }
        fprintf(
                stdout,
                "=End of mesh output=\n"
               );
    }




    void Mesh::print_info( std::string spacing )
    {
        fprintf(
                stdout,
                "%s=================\n"
                "%s%s:\n"
                "  %sSize:\t\t%f\n"
                "  %sVertices:\t\t%d\n",
                spacing.c_str(),
                spacing.c_str(),
                name_.c_str(),
                spacing.c_str(),
                scale_factor_,
                spacing.c_str(),
                vertices_->size()
               );

        for( GLuint i = 0; i < child_qty_; i++ )
        {
            children_[i]->print_info( spacing + "  " );
        }
    }

} //Model namespace.

