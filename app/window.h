/**
 * \file window.h
 * \author Thomas R. Carrel
 *
 * \brief Window object declaration.
 */

#ifndef WINDOW_H
#define WINDOW_H

#include<GL/glew.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_opengl.h>

#include<GL/glu.h>

#include<stdio.h>

#include "../constants.h"
#include "../shader_program.h"

#include<glm/glm.hpp>


//  Unfortunately, SDL2 windows using an OpenGL context don't work correctly
// over a remote xserver, so putting this in was meaningless, but I'm leaving
// it here in case it gets fixed in a future update.
//#define REMOTE_WINDOW

namespace App
{

    /**  The class for the game window.  Even though the game displays
     * fullscreen.
     */
    class Window
    {
        public:
            ~Window( void );

            void    init( void );

            bool    good( void );
            bool    ready( void );

            float   aspect( void );

            /** Get the screen width.
             */
            inline int  w( void ) { return mode_.w; }
            /** Get the screen height.
             */
            inline int  h( void ) { return mode_.h; }


            void    swap( void );
            void    redraw( void );

#ifdef DEBUG
            void    debug_draw( Shader* );
#endif

            SDL_GLContext* gl( void );

            friend class Application;

        private:
            //        const       SDL_VideoInfo* info_;

            Window( void );
            Window( glm::vec3 );
            Window( glm::vec4 );
            Window( float, float, float );

            void init_gl( void );

            const GLfloat   clear_color_[4]; ///< The clear color for OpenGL.
            bool            is_good_; ///< Window condition.

            SDL_Window*     window_; ///<  Address of the actual window, needed
                                     ///< for drawing.
            SDL_GLContext   gl_; ///< The OpenGL context for this window.

            string          title_; ///< The window title.
            SDL_DisplayMode mode_; ///< The display mode for the window.
            int             pos_x_, ///< Window horizontal position.
                            pos_y_, ///< Window vertical position.
                            bpp_; ///< Bits Per Pixel

            Uint32          flags_; ///< SDL2 fllags related to the window.
            float           aspect_; ///< The aspect ratio of the window.

    };

} //App namespace.

#endif
