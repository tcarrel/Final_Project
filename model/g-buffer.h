/**
 *
 * @file g-buffer.h
 * @author Thomas R. Carrel
 *
 * @brief Provides functionality for deferred/multipass shading.
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

    /** Manages the buffers for multipass rendering.
     */
    class G_Buffer
    {
        public:
            G_Buffer( App::Window* );


            //set_vao( );

        private:
            struct
            {
                /** Handle for the overall frame buffer. */
                GLuint Buffer;
                /** Handle for the position texture. */
                GLuint Position;
                /** Handle for the normal texture. */
                GLuint Normal;
                /** Handle for the albedo and specular texture. */
                GLuint Albedo_Spec;
            } g;
            /** Depth buffer. */
            GLuint rbo_depth_;
    };

} //Model namespace.

#endif /*_G_BUFFER_H_*/
