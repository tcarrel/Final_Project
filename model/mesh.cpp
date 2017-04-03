/**
 * \file mesh.cpp
 * \author Thomas R. Carrel
 *
 * \brief Definitions for Mesh class.
 */


#include "mesh.h"

#include "../shader_program.h"
#include "../app/window.h"
#include "../colors.h"

#include "obj_loader/obj.h"

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
     * \param name Each loaded mesh will be given a unique name that can be
     * used later to identify them.
     * \param m The rendering mode to be used for this mesh.
     */
    Mesh::Mesh( const std::string& name, GLenum m = GL_TRIANGLES ) :
        vertices_( new Vertex_Array ),
        verts_sent_to_gpu_( false ),
        qty_( 0 ),
        mode_( m ),
        vbo_( 0 ),
        vao_( 0 ),
        scale_factor_( 1.0f ),
        child_qty_( 0 ),
        children_( NULL ),
        name_( name )
        , qty_in_use_( 1 )
    {}




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






    /** For now, this will be responsible for sending all the draw calls to
     * the gpu.  Later, this will be responsible only for creating command
     * packets and sending those to the command buffer.
     * \param vp The view-projection matrix.
     */
    void Mesh::draw( const glm::mat4& vp ) throw( Scene_Graph_Exception )
    {

        if( !shader_ )
        {
            fprintf( stderr, "Name: %s\n", name_.c_str() );
            throw( Scene_Graph_Exception(
                        "No shader program set to mesh.\n" ) );
        }

        shader_->use_program();

        glBindVertexArray( vao_ );

        shader_->set_uniform( "vp", vp );
        fprintf(
                stderr,
                "Name: %s\tscale: %f\n",
                name_.c_str(),
                scale_factor_ );

        shader_->set_uniform( "sf", scale_factor_ );

        glDrawArrays( mode_, 0, qty_ );

        for( GLuint i = 0; i < child_qty_; i++ )
        {
            children_[i]->draw( vp );
        }
    }


    /**  Set the default shader program to be used when rendering this mesh.
     * \param p A pointer to the Shader object that will be used.
     */
    void Mesh::set_shader( Shader* p )
    {
        shader_ = p->get_ptr();
        for( GLuint i = 0; i < child_qty_; i++ )
        {
            children_[i]->set_shader(p);
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
                sizeof(Vertex),
                (void*) 0
                );
        glEnableVertexAttribArray( 1 );
        glVertexAttribPointer(
                1,
                4,
                GL_FLOAT,
                GL_FALSE,
                sizeof(Vertex),
                (void*) (3 * sizeof(GLfloat))
                );

        verts_sent_to_gpu_ = true;
        /*
           delete vertices_;
           vertices_ = NULL;
           */
    }






    /** Add a child mesh.
     * \param child The mesh to be added.
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

