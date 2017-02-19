/**
 * \file app.cpp
 * \author Thomas R. Carrel
 *
 * \brief Application framework definition.
 */

#include "app.h"
#include "window.h"

#include "../model/mesh.h"



/*
   extern SHADER_TYPE_NAME SIMPLE_v;
   extern SHADER_TYPE_NAME SIMPLE_f;
   */

#include "../shader_externs.h"


namespace App
{


    /**  Ctor.
     *   Creates the window object for the game and initializes it.
     */
    Application::Application( void ) :
        window_( new Window ), input_( window_ )
    {

        start_up();

        if( window_->good() )
        {
#ifdef DEBUG
            fprintf( stderr, "Window created successfully.\n" );
#endif
        }
        else
        {
            fprintf( stderr, "Failed to create window.\n" );
        }

    }





    /**  Initializes SDL2 and the window object.
    */
    void Application::start_up( void )
    {
        SDL_Init( SDLSYSTEMS );
        if( window_->good() )
        {
            window_->init();
        }
    }





    /**  Game main loop.
     *     This contains the main loop of the game as well as performing the final
     *   bit of initialization before the loop begins.
     */
    int Application::run( void )
    {


        if( window_->good() )
        {
#ifdef DEBUG
            //The following... should all be removed later...
            glPointSize(40.0f);
#endif

            mesh_ = new Model::Mesh( window_, GL_TRIANGLES );

            shader_ = new Shader;
            shader_->add_code( &SIMPLE_v, VERTEX_SHADER );
            shader_->add_code( &SIMPLE_f, FRAGMENT_SHADER );

            if( shader_->compile() == ERROR )
            {
                fprintf(
                        stderr,
                        "Could not compile shaders.\n\n"
                       );

            }

            shader_->print();

            //window_->debug_draw( shader_ );
            //Remove to here.

            mesh_->set_shader( shader_ );

            mesh_->draw( NULL );

            window_->swap();


            //            SDL_Delay(3000); /// Replace with a typical game loop.

            while( 1 )
            {
                input_.process();
            }

        }

        return 0;
    }





    /**  Dtor.
     *     Resposible for all de-initialization and cleanup.
     */
    Application::~Application( void )
    {
        SDL_Quit();

        if( shader_ )
        {
            delete shader_;
        }

        if( window_ )
        {
            delete window_;
        }

    }

} //App namespace.
