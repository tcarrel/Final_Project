/**
 *
 * \file texture.h
 * \author Thomas R. Carrel
 *
 * \brief An object for loading textures.
 */

#include<GL/glew.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_opengl.h>

#include<GL/gl.h>
#include<GL/freeglut.h>

#include<SOIL/SOIL.h>

#include<string>

#ifndef  _TEXTURE_BASE_H_
# define _TEXTURE_BASE_H_


namespace Model
{

    namespace Texture
    {

        /**  Base class for loading textures.
        */
        class Texture_base
        {
            public:

                Texture_base();
                virtual ~Texture_base( void ) {}

                /** Return the location of the texture on the GPU.
                 */
                GLuint operator()( void )
                { 
                    return handle_;
                }

                void error_check( unsigned char*, std::string& );

            protected:

                GLuint  handle_;
        };

    } //Texture namespace.

} //Model namespace.
#endif
