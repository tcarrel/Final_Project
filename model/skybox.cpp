/**
 *
 * @file skybox.cpp
 * @author Thomas R. Carrel
 *
 */



#include "skybox.h"
#include "../shaders.h"

#include<climits>

const GLuint SKYBOX_V_ID = UINT_MAX - 15;
const GLuint SKYBOX_F_ID = UINT_MAX - 30;

namespace Model
{
    Skybox::Skybox(
            const std::string& lef,
            const std::string& rig,
            const std::string& top,
            const std::string& bot,
            const std::string& fro,
            const std::string& bac )
    {
        std::string* faces = new std::string[6];
        faces[0] = rig; faces[1] = lef; faces[2] = top;
        faces[3] = bot; faces[4] = bac; faces[5] = fro;
        load_textures( faces );
        delete [] faces;
        faces = NULL;

        //Hard-coded shader programs.
        SHADER_TYPE_NAME vertex(
                "#version 450 core\nlayout (location = 0) in vec3 position;\n"
                "out vec3 tex_coords;\nuniform mat4 projection;\n"
                "uniform mat4 view;\nvoid main()\n{\n"
                "  gl_Position = projection * view * vec4(position, 1.0);\n "
                " tex_coords  = position;\n}\n", 222, SKYBOX_V_ID, "SKYBOX_v" );

        SHADER_TYPE_NAME fragment(
                "#version 450 core\n"
                "in  vec3 tex_coords;\n"
                "out vec4 color;\n"
                "uniform samplerCube skybox;\n"
                "void main()\n"
                "{\n"
                "  color = texture(skybox, tex_coords);\n"
                "}\n"
                ,
                138,
                SKYBOX_F_ID,
                "SKYBOX_f"
                );






        //Hard-coded vertices will work fine.
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


    }



    void Skybox::load_textures( std::string* faces )
    {
        GLenum type = GL_TEXTURE_CUBE_MAP;

        int width   =   0,
            height  =   0;
        unsigned char* image = NULL;

        glGenTextures(1, &texture_handle_);
        glBindTexture( type, texture_handle_ );

        for( GLuint i = 0; i < 6; i++ )
        {
            image = SOIL_load_image(
                    faces[i].c_str(),
                    &width,
                    &height,
                    0,
                    SOIL_LOAD_RGB );

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
        }

        //Specify image parameters.
        glTexParameteri( type, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
        glTexParameteri( type, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        glTexParameteri( type, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
        glTexParameteri( type, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
        glTexParameteri( type, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE );
    }

} //Model namespace.




/*
*/
