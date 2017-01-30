
#ifndef WINDOW_H
#define WINDOW_H

#include"constants.h"

#include<GL/glew.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_opengl.h>

#include<GL/glu.h>
//#include<GL/freeglut.h>

#include<iostream>
using std::string;
using std::cerr;
using std::endl;
using std::cout;

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

        SDL_Window*     window_;
        SDL_GLContext   gl_;

        string          title_;
        SDL_DisplayMode mode_;
        int             pos_x_, pos_y_, bpp_;
        const GLfloat   clear_color_[4];

        Uint32          flags_;
        double          aspect_;
};

#endif
