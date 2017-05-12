



#include "default.texture.h"

#include "../../random.h"
#include "../../colors.h"
#include "../../helper_functions.h"



namespace Model
{
    namespace Texture
    {
        String_Color_Pair random_scp( void )
        {
            String_Color_Pair out;

            out.color   = Color::random_color() | Color::OPAQUE;

            out.str     = numtoa(out.color) + "_DEFAULT";

            return out;
        }



        Texture_Default::Texture_Default( const String_Color_Pair& sp ) :
            Texture_base( sp.str, GL_TEXTURE_2D ),
            color_( sp.color )
        {
            glBindTexture( type_, handle_ );

            

            //Tiling
            glTexParameteri(
                    type_,
                    GL_TEXTURE_WRAP_S,
                    GL_REPEAT );
            glTexParameteri(
                    type_,
                    GL_TEXTURE_WRAP_T,
                    GL_REPEAT );

            //Filtering
            glTexParameteri(
                    type_,
                    GL_TEXTURE_MIN_FILTER,
                    GL_NEAREST );
            glTexParameteri(
                    type_,
                    GL_TEXTURE_MAG_FILTER,
                    GL_NEAREST );

            fprintf( stderr, "TEST\n" );

            glTexImage2D(
                    type_,
                    0,
                    GL_RGBA,
                    1,
                    1,
                    0,
                    GL_RGBA,
                    GL_UNSIGNED_BYTE,
                    (unsigned char*) &color_
                    );

            fprintf( stderr, "TEST2\n" );
        }



        Texture_Default::Texture_Default( void ) :
            Texture_Default( random_scp() )
        {}




        Texture_Default::~Texture_Default( void )
        {

        }



    } //Texture namespace.
} //Model namespace.
