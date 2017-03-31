/**
 *
 * @file 2D.texture.cpp
 * @author Thomas R. Carrel
 *
 * @brief Defines the Texture_2D class.
 */


#include "texture_base.h"
#include "2D.texture.h"


namespace Model
{
    namespace Texture
    {

        /** Load an image file into a texture.
         * @param filename The name of the file to load.
         */
        Texture_2D::Texture_2D( const std::string& filename) :
            Texture_base(filename, GL_TEXTURE_2D)
        {
            if( loaded_ )
            {
                // The image has already been loaded and the base class has
                //already setup the object as needed.
                return;
            }

            unsigned char* image = NULL;
            int width, height;

            glBindTexture( type_, handle_ );

            //Tiling
            glTexParameteri( type_, GL_TEXTURE_WRAP_S, GL_REPEAT );
            glTexParameteri( type_, GL_TEXTURE_WRAP_T, GL_REPEAT );

            //Filtering
            glTexParameteri( type_, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
            glTexParameteri( type_, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR );

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
                 type_,
                 0,
                 GL_RGB,
                 width,
                 height,
                 0,
                 GL_RGB,
                 GL_UNSIGNED_BYTE,
                 image
                );

            glGenerateMipmap( type_ );

            //Image is no longed needed in system memory.
            SOIL_free_image_data( image ); 

            loaded_ = true;
        }

    } //Texture namespace.
} //Model namespace.
