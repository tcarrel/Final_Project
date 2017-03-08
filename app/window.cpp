/**
 * \file window.cpp
 * \author Thomas R. Carrel
 *
 * \brief Defines the Window object.
 */

#include "window.h"


namespace App
{

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
    Window::Window(void) :
        Window(0.7f, 0.5f, 0.25f )
    {}


    /** Create window using the first three elements in a vec4 to fill the
     * colors.
     * \param c Clear color.
     */
    Window::Window( glm::vec4 c ) :
        Window( c.x, c.y, c.z )
    {}
    

    /** Create window using a vec3 for the clear color.
     * \param c Clear color.
     */
    Window::Window( glm::vec3 c ) :
        Window( c.x, c.y, c.z )
    {}

    /** Create default window.  Also sets the clear color for OpenGL.  The
     * alpha value if fixed to 100%.
     * param r Red value as a percentage (between 0.0 and 1.0.)
     * param g Green value as a percentage (between 0.0 and 1.0.)
     * param b Blue value as a percentage (between 0.0 and 1.0.)
     */
    Window::Window( float r, float g, float b ) :
        clear_color_{r, g, b, 1.0f },
        is_good_( true ),
        window_( NULL ),
        gl_( NULL )
        {

            if( !(SDL_WasInit( SDL_INIT_EVERYTHING ) & SDL_INIT_VIDEO) )
            {
                SDL_InitSubSystem( SDL_INIT_VIDEO );
            }

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

#ifdef REMOTE_WINDOW
            mode_.w = 1024;
            mode_.h = 768;
#endif

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
            aspect_ = (float) mode_.w / (float) mode_.h;
#ifdef REMOTE_WINDOW
            pos_x_  =   20;
            pos_y_  =   20;
# else
            pos_x_  =   -1;
            pos_y_  =   -1;
#endif
            title_  =   TITLE;
            flags_  =   
                SDL_WINDOW_OPENGL |
#ifndef REMOTE_WINDOW
                SDL_WINDOW_FULLSCREEN |
                SDL_WINDOW_BORDERLESS |
# else
                SDL_WINDOW_RESIZABLE |
#endif
                SDL_WINDOW_ALLOW_HIGHDPI |
                0;
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
#ifndef REMOTE_WINDOW
                (pos_x_ > 0) ? pos_x_ : SDL_WINDOWPOS_UNDEFINED,
                (pos_y_ > 0) ? pos_y_ : SDL_WINDOWPOS_UNDEFINED,
#else
                SDL_WINDOWPOS_CENTERED,
                SDL_WINDOWPOS_CENTERED,
#endif
                mode_.w,
                mode_.h,
                flags_
                );

#ifndef REMOTE_WINDOW
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
#endif

        if( !window_ )
        {
            fprintf(
                    stderr, "%sCould not create SDL window.\n%s\n",
                    error_text,
                    SDL_GetError()
                    );
            is_good_ = false;
            return;
        }

#ifdef REMOTE_WINDOW
//        SDL_SetWindowBordered( window_ 
#endif

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
        if( !gl_ )
        {
            fprintf(
                    stderr,
                    "%s\tCould not create OpenGL context.\tSDL Error:\n%s\n",
                    error_text,
                    SDL_GetError()
                   );
            is_good_ = false;
        }

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
                    "%s\tCould not initialize OpenGL!\tGLU Error:\t%s\n\n",
                    error_text,
                    gluErrorString( error )
                   );
            error = glGetError();
            is_good_ = false;
            return;
        }

        glPolygonMode( GL_FRONT, GL_FILL );
        glEnable( GL_CULL_FACE );
        //glEnable( GL_DEPTH_TEST );
        glCullFace( GL_BACK );

        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        SDL_GL_SwapWindow( window_ );
    }



    /**  For checking the condition of the window.
    */
    bool Window::good(void)
    {
        return is_good_;
    }





    /**  Check if the window is ready for use, i.e. whether or not there is a
     * valid OpenGL context.
     */
    bool Window::ready(void)
    {
        return gl_ != NULL;
    }




    /**  Get window aspect ratio.
    */
    float Window::aspect(void)
    {
        return aspect_;
    }



    /**  A reference to the OpenGL context for this window.
    */
    SDL_GLContext* Window::gl(void)
    {
        return &gl_;
    }



    /**  Swaps the frame buffers.
     * May not be necessary later on.
     */
    void Window::swap( void )
    {
        SDL_GL_SwapWindow( this->window_ );
    }

    /**  Redraws the window after it's been minimized.
    */
    void Window::redraw( void )
    {
        SDL_RestoreWindow( this->window_ );
    }



#ifdef DEBUG
    void Window::debug_draw( Shader* s )
    {
        s->use_program();

        glClear( GL_COLOR_BUFFER_BIT );

        glDrawArrays( GL_POINTS, 0, 1 );

        this->swap();
    }
#endif


} //App namespace.
