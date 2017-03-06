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


#ifndef  _TEXTURE_H_
# define _TEXTURE_H_


namespace Model
{

    namespace Texture
    {
        enum Use{
            AS_TEXTURE, 
            AS_BUMP_MAP,
            AS_NORMAL_MAP,
            AS_CUBE_MAP,
            AS_SPECULARITY_MAP
        };
        /**  For loading texture and sending them to the gpu.
        */
        class Texture_base
        {
            public:
                virtual ~Texture_base( void )

                GLuint operator()( void )
                { 
                    return handle_;
                }

            private:

                GLuint  handle_;
                Use     use_;
        };

    } //Texture namespace.

} //Model namespace.
#endif
