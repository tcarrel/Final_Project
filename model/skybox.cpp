/**
 *
 * @file skybox.cpp
 * @author Thomas R. Carrel
 *
 */



#include "skybox.h"
#include "../shader_program.h"
#include "../shaders.h"
#include "../helper_functions.h"

#include<cstdio>
#include<climits>

#define TEX_ GL_TEXTURE0

namespace Model
{


    /** Creates a cubemap-based skybox.
     * @param rig The right (+X) face of the cube.
     * @param lef The left (-X) face of the cube.
     * @param top The top (+Y) face of the cube.
     * @param bot The bottom (-Y) face of the cube.
     * @param bac The back (+Z) face of the cube.
     * @param fro The front (-Z) face of the cube.
     */
    Skybox::Skybox(
            const std::string& rig,
            const std::string& lef,
            const std::string& top,
            const std::string& bot,
            const std::string& bac,
            const std::string& fro ) :
        program_handle_( new Shader ),
        wf_( 0 )
    {
        const std::string path = "resource/skybox/";

        std::string* faces = new::string[6];
        faces[0] = path + rig;
        faces[1] = path + lef;
        faces[2] = path + top;
        faces[3] = path + bot;
        faces[4] = path + bac;
        faces[5] = path + fro;

        /*
        program_handle_->add_code( get_shader( "SKYBOX_v" ) );
//        program_handle_->add_code( get_shader( "SKYBOX_g" ) );
        program_handle_->add_code( get_shader( "SKYBOX_f" ) );
        */
        program_handle_->add_code( "skybox.v.glsl" );
        program_handle_->add_code( "skybox.f.glsl" );

        if( program_handle_->compile( "Skybox" ) == ERROR )
        {
            fprintf(
                    stderr,
                    "%s",
                    red( "Could not compile skybox shader.\n\n" ).c_str()
                   );
        }
        else
        {
            fprintf( stderr,
                    "Cubemap shaders compiled successfully.\n" );
        }

        //Hard-coded vertices are sufficient.
        GLfloat vertices[] =
        {
            -1.0f,  1.0f, -1.0f,
            -1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,

            -1.0f, -1.0f,  1.0f,
            -1.0f, -1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f,

            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,

            -1.0f, -1.0f,  1.0f,
            -1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f, -1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f,

            -1.0f,  1.0f, -1.0f,
            1.0f,  1.0f, -1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            -1.0f,  1.0f,  1.0f,
            -1.0f,  1.0f, -1.0f,

            -1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f,  1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f,  1.0f,
            1.0f, -1.0f,  1.0f
        };
//        GLuint num_verts = 3 * 6 * 6;

        glGenVertexArrays( 1, &vao_ );
        glGenBuffers( 1, &vbo_ );

        glBindVertexArray( vao_ );

        glBindBuffer( GL_ARRAY_BUFFER, vbo_ );
        glBufferData(
                GL_ARRAY_BUFFER,
                sizeof(vertices),
                &vertices,
                GL_STATIC_DRAW
                );

        glEnableVertexAttribArray( 0 );
        glVertexAttribPointer(
                0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*) 0 );


        load_textures( faces );
        delete [] faces;
        faces = NULL;
    }



    void Skybox::load_textures( std::string* faces )
    {
        const GLenum type = GL_TEXTURE_CUBE_MAP;

        int w   =   0,
            h   =   0;

        unsigned char* image = NULL;

        glGenTextures(1, &texture_handle_);
        glBindTexture( type, texture_handle_ );
        glActiveTexture( TEX_ );

        //Unrolled loop
        image = SOIL_load_image(
                faces[0].c_str(),  &w, &h, NULL, SOIL_LOAD_RGB );
        check_SOIL_error( image, faces[0] );
        glTexImage2D(
                GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGB, w, h, 0,
                GL_RGB, GL_UNSIGNED_BYTE, image );
        SOIL_free_image_data( image );

        image = SOIL_load_image(
                faces[1].c_str(),  &w, &h, NULL, SOIL_LOAD_RGB );
        check_SOIL_error( image, faces[1] );
        glTexImage2D(
                GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGB, w, h, 0,
                GL_RGB, GL_UNSIGNED_BYTE, image );
        SOIL_free_image_data( image );

        image = SOIL_load_image(
                faces[2].c_str(),  &w, &h, NULL, SOIL_LOAD_RGB );
        check_SOIL_error( image, faces[2] );
        glTexImage2D(
                GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGB, w, h, 0,
                GL_RGB, GL_UNSIGNED_BYTE, image );
        SOIL_free_image_data( image );

        image = SOIL_load_image(
                faces[3].c_str(),  &w, &h, NULL, SOIL_LOAD_RGB );
        check_SOIL_error( image, faces[3] );
        glTexImage2D(
                GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGB, w, h, 0,
                GL_RGB, GL_UNSIGNED_BYTE, image );
        SOIL_free_image_data( image );

        image = SOIL_load_image(
                faces[4].c_str(),  &w, &h, NULL, SOIL_LOAD_RGB );
        check_SOIL_error( image, faces[4] );
        glTexImage2D(
                GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGB, w, h, 0,
                GL_RGB, GL_UNSIGNED_BYTE, image );
        SOIL_free_image_data( image );

        image = SOIL_load_image(
                faces[5].c_str(),  &w, &h, NULL, SOIL_LOAD_RGB );
        check_SOIL_error( image, faces[5] );
        glTexImage2D(
                GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGB, w, h, 0,
                GL_RGB, GL_UNSIGNED_BYTE, image );
        SOIL_free_image_data( image );

        image = NULL; w = 0; h = 0;

        //Specify image parameters.
        glTexParameteri( type, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
        glTexParameteri( type, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        glTexParameteri( type, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
        glTexParameteri( type, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
        glTexParameteri( type, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE );
        glBindTexture( type, 0 );
    }




    void Skybox::render( const glm::mat4& view, const glm::mat4& proj )
    {
        glDepthFunc( GL_LEQUAL );
        program_handle_->use_program();
        //  Remove the translation components of the view matrix before sending
        //it to the GPU.
        program_handle_->set_uniform( "view", glm::mat4( glm::mat3( view ) ) );
        program_handle_->set_uniform( "projection", proj );
        program_handle_->set_uniform( "wireframe", wf_ );

        glBindVertexArray( vao_ );
//        glActiveTexture( TEX_ );
        program_handle_->set_uniform( "sky", 0 );
        glBindTexture( GL_TEXTURE_CUBE_MAP, texture_handle_ );
        glDrawArrays( GL_TRIANGLES, 0, 36 );
        //glBindVertexArray( 0 );

        //glEnable( GL_CULL_FACE );
        glDepthFunc( GL_LESS );
    }




    void Skybox::set_wireframe( void )
    {
        wf_ = 1;
    }




    void Skybox::get_reflect_data( GLuint* tex, GLenum* tex_unit )
    {
        *tex        =   texture_handle_;
        *tex_unit   =   TEX_;
    }
} //Model namespace.

#undef TEX_
