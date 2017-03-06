/**
 *
 * \file texture_2D.cpp
 * \author Thomas R. Carrel
 *
 * \brief Defines the Texture_2D class.
 */


#include "texture_base.h"
#include "texture_2D.h"


namespace Model
{
    namespace Texture
    {

        /** Load an image file into a texture.
         * \param filename The name of the file to load.
         */
        Texture_2D::Texture_2D( std::string filename ) :
            Texture_base()
        {
            const GLenum t = GL_TEXTURE_2D;

            unsigned char* image = NULL;
            int width, height;

            glBindTexture( t, handle_ );

            //Tiling
            glTexParameteri( t, GL_TEXTURE_WRAP_S, GL_REPEAT );
            glTexParameteri( t, GL_TEXTURE_WRAP_T, GL_REPEAT );

            //Filtering
            glTexParameteri( t, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
            glTexParameteri( t, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR );

            image = SOIL_load_image
                (
                 filename.c_str(),
                 &width,
                 &height,
                 0,
                 SOIL_LOAD_RGBA
                );


            glTexImage2D
                (
                 t,
                 0,
                 GL_RGB,
                 width,
                 height,
                 0,
                 GL_RGB,
                 GL_UNSIGNED_BYTE,
                 image
                );

            glGenerateMipmap( t );

            SOIL_free_image_data( image );
        }

    } //Texture namespace.
} //Model namespace.
