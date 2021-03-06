/**
 *
 * @file texture_base.cpp
 * @author Thomas R. Carrel
 *
 * @brief Defines the base class (Texture_base) for the loading of textures.
 *
 */


#include<cstdio>

#include "texture_base.h"
#include "../../helper_functions.h"


namespace Model
{

    namespace Texture
    {

//        Tracking_List<Texture_base> Texture_base::list_;





        /** Ctor.
         * @param filename The filename passed in from the child class.
         * @param T The type enumeration from OpenGL.
         */
        Texture_base::Texture_base( const string& filename, const GLenum& T ) :
            file_(filename),
            type_(T),
            loaded_( false )
        {
            /*
            string name = filename + "_" + tex_type_to_string(T);
            Texture_base* tex = list_.get(name);


            if( tex && (tex->type_ == T) )
            {
                //Texture has already been loaded.
                handle_ = tex->handle_;
                loaded_ = true;
                return;
            }

            //Texture has not yet been loaded.
            list_.add( name, this );
            */

            glGenTextures( 1, &handle_ );
        }




        /** Check if the there was an error loading the image file.
         *
         * @param addr Pointer to the image.
         * @param filename Used for the error message, if necessary.
         */
        void Texture_base::error_check(
                unsigned char* addr,
                std::string& filename )
        {
            if( addr )
            {
                // No error.
                return;
            }

            fprintf(
                    stderr,
                    "Could not load texture file <%s>.\n",
                    filename.c_str()
                   );
        }


        //////////////////// "Local" helper functions.

        const string tex_type_to_string( GLenum T )
        {
            switch( T )
            {
                case GL_TEXTURE_1D:
                    return "TEXTURE_1D";
                case GL_TEXTURE_2D:
                    return "TEXTURE_2D";
                default:
                    return bright_red("UNIMPLENTED_or_UNKNOWN_TEXTURE");
            }
        }



        Texture_base::~Texture_base( void )
        {
            //Clear tracking list.
        }




        void Texture_base::print( void )
        {
            fprintf(
                    stderr,
                    "%s\n",
                    file_.c_str() );
        }
    } //Texture namespace.

} //Model namespace.
