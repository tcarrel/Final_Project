/**
 * \file window.cpp
 * \author Thomas R. Carrel
 */

#include"window.h"




/** Create default window.  Also sets the clear color for OpenGL.
 */
Window::Window(void) ://: info_( SDL_GetVideoInfo() )
    clear_color_{1.0f, 0.5f, 0.25f, 1.0f}
{
    if( !(SDL_WasInit( SDL_INIT_EVERYTHING ) & SDL_INIT_VIDEO) )
        SDL_InitSubSystem( SDL_INIT_VIDEO );

    if( 0 != SDL_GetDesktopDisplayMode(0, &mode_) )
    {
        fprintf(
                stderr,
                "WARNING!!\tCould not query display.\tSDL Error:\t%s\n",
                SDL_GetError()
                );
        mode_.w = 1024; mode_.h = 768; mode_.refresh_rate = 60;
    }

    bpp_ = SDL_BITSPERPIXEL(mode_.format);
    fprintf(
            stderr,
            "Display format selected:\n\n"
            "\tResolution\t%dx%d\n"
            "\tBPP\t\t%d\n"
            "\tFormat\t\t%d\n"
            "\tPixel Fmt Name\t%s\n\n",
            mode_.w,
            mode_.h,
            bpp_,
            mode_.format,
            SDL_GetPixelFormatName(mode_.format)
           );

    pos_x_  =   -1;
    pos_y_  =   -1;
    title_  =   TITLE;
    flags_  =   
        SDL_WINDOW_OPENGL |
        SDL_WINDOW_FULLSCREEN |
        SDL_WINDOW_BORDERLESS |
        SDL_WINDOW_ALLOW_HIGHDPI;
    window_ = NULL;
}



/** Window dtor.
 *  Kills the OpenGL context and closes the window.
 */
Window::~Window(void)
{
    if( gl_ )
        SDL_GL_DeleteContext( gl_ );

    if( window_ )
        SDL_DestroyWindow( window_ );
}



/**  Initialize window once 
 */
void Window::init(void)
{
    aspect_ = ((double) mode_.w) / ((double) mode_.h);

    window_ = SDL_CreateWindow(
            title_.c_str(),
            (pos_x_ > 0) ? pos_x_ : SDL_WINDOWPOS_UNDEFINED,
            (pos_y_ > 0) ? pos_y_ : SDL_WINDOWPOS_UNDEFINED,
            mode_.w,
            mode_.h,
            flags_
            );

    if( 0 > SDL_SetWindowFullscreen( window_, SDL_WINDOW_FULLSCREEN ) )
    {
        fprintf(
                stderr,
                "WARNING!!\tFailed to set window to fullscreen.\tSDL Error:\t%s\n",
                SDL_GetError() 
               );
    }
    if( !window_ )
        return;
    flags_ = SDL_GetWindowFlags( window_ );

    init_gl();
}



/**
 * Initialize OpenGL and all necessary extensions.
 */
void Window::init_gl(void)
{
    GLenum error = GL_NO_ERROR;

    gl_ = SDL_GL_CreateContext( window_ );

    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 4 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 5 );
    SDL_GL_SetAttribute(
            SDL_GL_CONTEXT_PROFILE_MASK,
            SDL_GL_CONTEXT_PROFILE_CORE );
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1);

    SDL_GL_MakeCurrent( window_, gl_ );

    glewExperimental    = GL_TRUE;
    GLenum glew_error   = glewInit();
    if( glew_error != GLEW_OK )
        fprintf(
                stderr,
                "ERROR@@\tUnable to initialize GLEW.\tGLEW Error:\t%s\n",
                glewGetErrorString( glew_error )
               );

    if( SDL_GL_SetSwapInterval(1) < 0 )
        fprintf(
                stderr,
                "WARNING!!\tUnable to set VSync.\tSDL Error:\t%s\n",
                SDL_GetError()
               );

    /*
     * Additional OpenGL initializations go here.
     */
    glClearColor(
            clear_color_[0],
            clear_color_[1],
            clear_color_[2],
            clear_color_[3]
            );
    SDL_GL_SwapWindow(window_);

    error = glGetError();
    while( error !=  GL_NO_ERROR )
    {
        fprintf(
                stderr,
                "ERROR##\tInitializing OpenGL!\tGLU Error:\t%s\t",
                gluErrorString( error )
               );
        error = glGetError();
    }

    glClear( GL_COLOR_BUFFER_BIT );
    SDL_GL_SwapWindow(window_);
}



/**  For checking the condition of the window.
 */
bool Window::good(void)
{
    return window_ != NULL;
}



/**  Get window aspect ratio.
 */
double Window::aspect(void)
{
    return aspect_;
}



/**  A reference to the OpenGL context for this window.
 */
SDL_GLContext& Window::gl(void)
{
    return gl_;
}



/**  Draws to the window... ...
 */
void Window::draw( )
{
}
