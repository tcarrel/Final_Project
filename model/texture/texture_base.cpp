/**
 *
 * \file texture_base.cpp
 * \author Thomas R. Carrel
 *
 * \brief Defines the base class (Texture_base) for the loading of textures.
 *
 */


#include<cstdio>
#include "texture_base.h"


namespace Model
{

    namespace Texture
    {

        Tracking_List<Texture_base> Texture_base::list_;

        /** Ctor.
         */
        Texture_base::Texture_base( GLenum T ) :
            type_(T),
            loaded_( false )
        {
            glGenTextures( 1, &handle_ );
        }




        /** Check if the there was an error loading the image file.
         *
         * \param addr Pointer to the image.
         * \param filename Used for the error message, if necessary.
         */
        void Texture_base::error_check( unsigned char* addr, std::string& filename )
        {
            // No error.
            if( addr )
            {
                return;
            }

            fprintf(
                    stderr,
                    "Could not load texture file <%s>.\n",
                    filename.c_str()
                   );
        }

    } //Texture namespace.

} //Model namespace.
