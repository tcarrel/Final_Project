/**
 *
 * \file texture_base.h
 * \author Thomas R. Carrel
 *
 * \brief The base class for loading textures.
 */

#include<GL/glew.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_opengl.h>

#include<GL/gl.h>

#include<SOIL/SOIL.h>

#include<string>
using std::string;

#ifndef  _TEXTURE_BASE_H_
# define _TEXTURE_BASE_H_

#include "../../tracking_list.h"

namespace Model
{

    namespace Texture
    {

        class Texture_list;

        /**  Base class for loading textures.
        */
        class Texture_base
        {
            public:
                virtual ~Texture_base( void ) {}

                /** Return the location of the texture on the GPU.
                 */
                GLuint operator()( void )
                { 
                    return handle_;
                }

                void error_check( unsigned char*, std::string& );

            protected:
                //Object can only be created as part of a child object.
                Texture_base( const string&, const GLenum& );

                /**  The 'name' of the texture on the gpu.
                 */
                GLuint                              handle_;
                /**  Stores the type of texture, this cannot be determined at
                 * compile time.
                 */
                const   GLenum                      type_;
                /** Whether or not the texture has been loaded.
                 */
                bool                                loaded_;
                /** We want to avoid repeatedly loading the same texture.
                 */
                static  Tracking_List<Texture_base> list_;
        };

        extern const string tex_type_to_string( GLenum );

    } //Texture namespace.

} //Model namespace.
#endif
