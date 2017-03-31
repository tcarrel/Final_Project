/**
 * 
 * @file 2D.texture.h
 * @author Thomas R. Carrel
 *
 * @brief Declares the Texture_2D class.
 *
 */


#include<GL/glew.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_opengl.h>

#include<GL/gl.h>
//#include<GL/freeglut.h>

#include<SOIL/SOIL.h>

#include<string>


#ifndef  _TEXTURE_H_
# define _TEXTURE_H_


namespace Model
{

    class Texture_base;

    namespace Texture
    {
        /**  For loading images into 2D textures on the GPU.
        */
        class Texture_2D : public Texture_base
        {
            public:
                Texture_2D( const std::string& );

                /** Dtor.
                 */
                ~Texture_2D( void ) {}
        };

    } //Texture namespace.

} //Model namespace.
#endif
