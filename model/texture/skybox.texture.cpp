/**
 *
 * @file cube.texture.cpp
 * @author Thomas R. Carrel
 *
 */



#include "texture_base.h"
#include "skybox.texture.h"


namespace Model
{
    namespace Texture
    {
        /**  Loads a skybox from six image files.
         * @param lef The left image.
         * @param rig The right image.
         * @param top The top image.
         * @param bot The bottom image.
         * @param fro The front image.
         * @param bac The back image.
         */
        Skybox_Texture::Skybox_Texture(
                const string& lef,
                const string& rig,
                const string& top,
                const string& bot,
                const string& fro,
                const string& bac ) :
            Texture_base(
                    lef + rig + top + bot + fro + bac,
                    GL_TEXTURE_CUBE_MAP )
        {
            //Load images.
            string faces[6];
            int width   =   0,
                height  =   0;
            unsigned char* image = NULL;

            faces[0] = rig; faces[1] = lef; faces[2] = top;
            faces[3] = bot; faces[4] = bac; faces[5] = fro;

            glGenTextures(1, &handle_);
            assert( type_ == GL_TEXTURE_CUBE_MAP );
            glBindTexture( type_, handle_ );

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
            glTexParameteri( type_, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
            glTexParameteri( type_, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
            glTexParameteri( type_, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
            glTexParameteri( type_, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
            glTexParameteri( type_, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE );
        }



    } //Texture namespace.
} //Model namespace.
