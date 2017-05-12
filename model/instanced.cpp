/**
 *
 * @file instanced.cpp
 * @author Thomas R. Carrel
 *
 */



#include "instanced.h"
#include "mesh.h"

#include "obj_loader/obj.h"

#include "../random.h"
#include<cmath>



namespace Model
{


    /**  Ctor.
    */
    Instanced::Instanced(
            GLuint          q,
            GLfloat         r,
            GLfloat         o,
            GLfloat         s,
            const string&   n,
            OBJ::OBJ_File*  obj_loader,
            bool            coloring) :
        qty_(q), 
        model_mats_( new glm::mat4[q] ),
        trans_mats_( new glm::mat4[q] ),
        radius_( r ),
        offset_( o ),
        max_scale_( s ),
        mesh_( NULL ),
        shader_( new Shader ),
        buffer_( 0 )
    {
        mesh_ = obj_loader->load_file( n, shader_, coloring, 1 );
        shader_->add_code( "asteroids.f.glsl" );
        shader_->add_code( "asteroids.v.glsl" );

        if( shader_->compile( "Instanced" ) == ERROR )
        {
            fprintf(
                    stderr,
                    red("%s").c_str(),
                    "Could not compile instanced rendering shader.\n\n"
                   );
        }
        else
        {
            fprintf( stderr,
                    "Instanced rendering shaders compiled successfully.\n" );
        }

        GLint max = 2 * offset_ * 100;
        GLint min = 0;

        for( GLuint i = 0; i < qty_; i++ )
        {
            GLfloat     angle           =   (GLfloat) i / (GLfloat)qty_ * 360.0f;
            GLfloat     displacement    =   get_rand( min, max ) / 100.0f - offset_; 
            GLfloat     x               =   sin(angle) * radius_ + displacement;
            displacement                =   get_rand( min, max ) / 100.0f - offset_;
            GLfloat     y               =   displacement * 0.4f;
            displacement                =   get_rand( min, max ) / 100.0f - offset_;
            GLfloat     z               =   cos(angle) * radius_ + displacement;
            GLfloat     scale           =   get_rand( 0, max_scale_ ) / 100.0f + 0.05f;
            GLfloat     rot_angle       =   get_rand( 0, 360 );
            glm::vec3   rot_axis        =   glm::vec3(
                    get_rand( -1.0f, 1.0f ),
                    get_rand( -1.0f, 1.0f ),
                    get_rand( -1.0f, 1.0f )
                    );

            glm::mat4   mat             =   glm::translate( mat, glm::vec3(x, y, z) );
            trans_mats_[i]              =   mat;
            mat                         =   glm::scale( mat, glm::vec3(scale) );
            mat                         =   glm::rotate( mat, rot_angle, rot_axis );

            model_mats_[i]              =   mat;
        }

        glGenBuffers( 1, &buffer_ );
        glBindBuffer( GL_ARRAY_BUFFER, buffer_ );
        glBufferData(
                GL_ARRAY_BUFFER,
                qty_ * sizeof(glm::mat4),
                &model_mats_[0],
                GL_STATIC_DRAW );

        if( mesh_ )
        {
            mesh_->bind_vao();
            /*
            glEnableVertexAttribArray( 2 );
            glVertexAttribPointer(
                    2,
                    2,
                    GL_FLOAT,
                    GL_FALSE,
                    sizeof(glm::vec2),
                    );
                    */
            for( GLuint a = 3; a < 7; a++ )
            {
                glEnableVertexAttribArray( a );
                glVertexAttribPointer(
                        a,
                        4,
                        GL_FLOAT,
                        GL_FALSE,
                        sizeof(glm::mat4),
                        (GLvoid*) ((a - 3) * sizeof(glm::vec4))
                        );
            }

            for( GLuint a = 3; a < 7; a++ )
            {
                glVertexAttribDivisor( a, 1 );
            }
        }
    }



    /** Dtor.
    */
    Instanced::~Instanced( void )
    {
        shader_->delete_this();
        if( model_mats_ )
        {
            delete [] model_mats_;
        }
        if( trans_mats_ )
        {
            delete [] trans_mats_;
        }
        if( mesh_ )
        {
            mesh_->delete_this();
        }
    }



    bool Instanced::first_draw_ = true;


    void Instanced::render( const glm::mat4& view, const glm::mat4& proj )
    {
        if( !mesh_ )
        {
            fprintf( stderr, "Instanced has no mesh.\n" );
            return;
        }

        if( first_draw_ )
        {
            first_draw_ = false;
            fprintf( stderr, "Drawing Instanced.\n" );
        }

        shader_->use_program();

        mesh_->bind_texture();
        shader_->set_uniform( "projection", proj );
        shader_->set_uniform( "view", view );
       
        mesh_->bind_vao();

        glDrawArraysInstanced( GL_TRIANGLES, 0,  1, qty_ );
    }

} //Model namespace.
