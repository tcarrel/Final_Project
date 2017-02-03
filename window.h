/**
 * \file window.h
 * \author Thomas R. Carrel
 */

#ifndef WINDOW_H
#define WINDOW_H

#include"constants.h"

#include<GL/glew.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_opengl.h>

#include<GL/glu.h>
//#include<GL/freeglut.h>

#include<stdio.h>


/**  The class for the game window.  Even though the game displays fullscreen.
 */
class Window
{
    public:
        Window( void );
        ~Window( void );

        void    init( void );

        bool    good( void );
        double  aspect( void );

        void    draw( void );

        SDL_GLContext& gl( void );

    private:
//        const       SDL_VideoInfo* info_;

        void init_gl( void );

        SDL_Window*     window_; ///< Address of the actual window, needed for
                                 ///< drawing.
        SDL_GLContext   gl_; ///< The OpenGL context for this window.

        string          title_; ///< The window title.
        SDL_DisplayMode mode_; ///< The display mode for the window.
        int             pos_x_, ///< Window horizontal position.
                        pos_y_, ///< Window vertical position.
                        bpp_; ///< Bits Per Pixel
        const GLfloat   clear_color_[4]; ///< The clear color for OpenGL.

        Uint32          flags_; ///< SDL2 fllags related to the window.
        double          aspect_; ///< The aspect ratio of the window.
};

#endif
