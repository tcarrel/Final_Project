/**
 *
 * @file g-buffer.h
 * @author Thomas R. Carrel
 *
 * @brief Used for two-pass rendering. (Deferred shading)
 *
 */

#include<GL/glew.h>

#include<SDL2/SDL.h>
#include<SDL2/SDL_opengl.h>

#include<GL/glu.h>

#include<glm/glm.hpp>
#include<glm/gtx/transform.hpp>




#ifndef  _G_BUFFER_H_
# define _G_BUFFER_H_

namespace App
{
    class Window;
}

namespace Model
{

    class G_Buffer
    {
        public:
            G_Buffer( App::Window* );


            //set_vao( );

        private:
            struct
            {
                GLuint Buffer;
                GLuint Position;
                GLuint Normal;
                GLuint Albedo_Spec;
            } g;
            GLuint rbo_depth_;
    };

} //Model namespace.

#endif /*_G_BUFFER_H_*/
