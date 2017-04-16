/**
 *
 * @file cube.texture.h
 * @author Thomas R. Carrel
 *
 */


#include<GL/glew.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_opengl.h>

#include<GL/gl.h>

#include<SOIL/SOIL.h>

#include<string>

#include<assert.h>


#ifndef  _SKYBOX_H_
# define _SKYBOX_H_

namespace Model
{
    namespace Texture
    {
        class Texture_base;

        class Skybox_Texture : public Texture_base
        {
            public:
                Skybox_Texture(
                        const string&, const string&,
                        const string&, const string&,
                        const string&, const string& );
            private:
                GLfloat vertices;
        };
    } //Texture namespace.
} //Model namespace.

#endif /*_SKYBOX_H_*/

