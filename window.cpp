/**
 * \file window.cpp
 * \author Thomas R. Carrel
 */

#include"window.h"


/**
 * Pre-formatted warning text.
 */
char warning_text[] = "\033[1;35;40mWARNING!!\033[0m";

/**
 * Pre-formatted error text.
 */
char error_text[]   = "\033[1;31;40mERROR!!\033[0m";





/** Create default window.  Sets a hard coded clear color for OpenGL, ideally,
 * this ctor should not be used in the final game..
 */
Window::Window(void) ://: info_( SDL_GetVideoInfo() )
    Window(1.0f, 0.5f, 0.25f, 1.0f)
{}




/** Create default window.  Also sets the clear color for OpenGL.
 * param r Red value as a percentage (between 0.0 and 1.0.)
 * param g Green value as a percentage (between 0.0 and 1.0.)
 * param b Blue value as a percentage (between 0.0 and 1.0.)
 * param a Alpha value as a percentage (between 0.0 and 1.0.)
 */
Window::Window( float r, float g, float b, float a ) :
    clear_color_{r, g, b, a},
    is_good_( true ),
    window_( NULL ),
    gl_( NULL )
{

    if( !(SDL_WasInit( SDL_INIT_EVERYTHING ) & SDL_INIT_VIDEO) )
        SDL_InitSubSystem( SDL_INIT_VIDEO );

    if( 0 != SDL_GetDesktopDisplayMode(0, &mode_) )
    {
        fprintf(
                stderr,
                "%s\tCould not query display.\tSDL Error:\t%s\n",
                error_text,
                SDL_GetError()
               );
        is_good_ = false;
        return;
    }

    bpp_ = SDL_BITSPERPIXEL(mode_.format);
    fprintf(
            stderr,
            "Display format selected:\n"
            "+===================+===========================+\n"
            "| Resolution        | %dx%d\t\t\t|\n"
            "| BPP               | %d\t\t\t|\n"
            "| Format            | %d\t\t\t|\n"
            "| Pixel Format Name | %s\t|\n"
            "+===================+===========================+\n\n",
            mode_.w,
            mode_.h,
            bpp_,
            mode_.format,
            SDL_GetPixelFormatName(mode_.format)
           );
    aspect_ = (double) mode_.w / (double) mode_.h;

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

    if( !is_good_ )
    {
        return;
    }

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
        is_good_ = false;
        fprintf(
                stderr,
                "%s\tFailed to set window to fullscreen.\t"
                "SDL Error:\t%s\n",
                error_text,
                SDL_GetError() 
               );
        return;
    }

    if( !window_ )
    {
        is_good_ = false;
        return;
    }

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

    SDL_GL_SetAttribute( SDL_GL_RED_SIZE,       5 );
    SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE,     5 );
    SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE,      5 );
    SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE,     16 );
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER,   1 );

    SDL_GL_MakeCurrent( window_, gl_ );

    glewExperimental    = GL_TRUE;
    GLenum glew_error   = glewInit();
    if( glew_error != GLEW_OK )
    {
        fprintf(
                stderr,
                "%s\tUnable to initialize GLEW.\tGLEW Error:\t%s\n",
                error_text,
                glewGetErrorString( glew_error )
               );
        is_good_ = false;
        return;
    }

    if( SDL_GL_SetSwapInterval(1) < 0 )
    {
        fprintf(
                stderr,
                "%s\tUnable to set VSync.\tSDL Error:\t%s\n",
                warning_text,
                SDL_GetError()
               );
    }

    /*
     * Additional OpenGL initializations go here.
     */
    glClearColor(
            clear_color_[0],
            clear_color_[1],
            clear_color_[2],
            clear_color_[3]
            );
    SDL_GL_SwapWindow( window_ );

    error = glGetError();
    while( error !=  GL_NO_ERROR )
    {
        fprintf(
                stderr,
                "%s\tInitializing OpenGL!\tGLU Error:\t%s\t",
                error_text,
                gluErrorString( error )
               );
        error = glGetError();
        is_good_ = false;
        return;
    }

    glClear( GL_COLOR_BUFFER_BIT );
    SDL_GL_SwapWindow( window_ );
}



/**  For checking the condition of the window.
*/
bool Window::good(void)
{
    return is_good_;
}



/**  Get window aspect ratio.
*/
double Window::aspect(void)
{
    return aspect_;
}



/**  A reference to the OpenGL context for this window.
*/
SDL_GLContext* Window::gl(void)
{
    return &gl_;
}



/**  Draws to the window... ...
 * May not be necessary later on.
 */
inline void Window::draw( )
{
    if( is_good_ )
    {
        SDL_GL_SwapWindow(this->window_);
    }
}



#ifdef DEBUG
void Window::debug_draw( Shader* s )
{
    s->use_program();

    glClear( GL_COLOR_BUFFER_BIT );

    /*
       GLint test[3];
       test[0] = 1;
       test[1] = 1;
       test[2] = 1;
       */


    glDrawArrays( GL_POINTS, 0, 1 );

    this->draw();
}
#endif
