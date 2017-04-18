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

namespace Model
{
    Skybox::Skybox(
            const std::string& rig,
            const std::string& lef,
            const std::string& top,
            const std::string& bot,
            const std::string& bac,
            const std::string& fro ) :
        program_handle_( new Shader )
    {
        const std::string path = "resource/skybox/";

        std::string* faces = new::string[6];
        faces[0] = path + rig;
        faces[1] = path + lef;
        faces[2] = path + top;
        faces[3] = path + bot;
        faces[4] = path + bac;
        faces[5] = path + fro;

        program_handle_->add_code( get_shader( "SKYBOX_v" ) );
        program_handle_->add_code( get_shader( "SKYBOX_f" ) );
        fprintf( stderr, "Compiling Cubemap shaders.\n" );

        if( program_handle_->compile() == ERROR )
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
        GLuint num_verts = 3 * 6 * 6;

        glGenVertexArrays( 1, &vao_ );
        glBindVertexArray( vao_ );

        glGenBuffers( 1, &vbo_ );
        glBindBuffer( GL_ARRAY_BUFFER, vbo_ );
        glBufferData(
                GL_ARRAY_BUFFER,
                sizeof(GLfloat) * num_verts,
                vertices,
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
        GLenum type = GL_TEXTURE_CUBE_MAP;

        glGenTextures(1, &texture_handle_);
        glBindTexture( type, texture_handle_ );
        glActiveTexture( GL_TEXTURE1 );

        for( GLuint i = 0; i < 6; i++ )
        {
            int width   =   0,
                height  =   0;

            unsigned char* image = SOIL_load_image(
                    faces[i].c_str(),
                    &width,
                    &height,
                    NULL,
                    SOIL_LOAD_RGB );

            if( image )
            {
                fprintf(
                        stderr,
                        "Texture image loaded:\n  Filename\t< %s >\n"
                        "  Size\t\t< %i x %i >\n",
                        faces[i].c_str(), width, height );
            }
            else
            {
                fprintf(
                        stderr,
                        "Image load error <%s>:\n%s\n",
                        faces[i].c_str(),
                        SOIL_last_result() );
            }

            glTexImage2D(
                    GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                    0,
                    GL_RGB,
                    width,
                    height,
                    0,
                    GL_RGB,
                    GL_UNSIGNED_BYTE,
                    image
                    );

            SOIL_free_image_data( image );
        }

        //Specify image parameters.
        glTexParameteri( type, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
        glTexParameteri( type, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        glTexParameteri( type, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
        glTexParameteri( type, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
        glTexParameteri( type, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE );
        glBindTexture( GL_TEXTURE_CUBE_MAP, 0 );
    }




    void Skybox::render( const glm::mat4& view, const glm::mat4& proj )
    {
        program_handle_->use_program();
        program_handle_->set_uniform( "projection", proj );
        //  Remove the translation components of the view matrix before sending
        //it to the GPU.
        program_handle_->set_uniform( "view", glm::mat4( glm::mat3( view ) ) );

        glDisable( GL_CULL_FACE );

        glBindVertexArray( vao_ );
        glBindTexture( GL_TEXTURE_CUBE_MAP, texture_handle_ );
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray( 0 );

        glEnable( GL_CULL_FACE );
    }


} //Model namespace.




/*
*/
