/**
 * \file app.cpp
 * \author Thomas R. Carrel
 *
 * \brief Application framework definition.
 */

#include "app.h"
#include "window.h"

#include "../model/scene_graph.h"
#include "../model/sg_setup.h"
#include "../model/mesh.h"
#include "../model/model.h"



/*
   extern SHADER_TYPE_NAME SIMPLE_v;
   extern SHADER_TYPE_NAME SIMPLE_f;
   */

#include "../shader_externs.h"

namespace App
{

    Application::Application( void ) :
        Application( (int) 1, (char**) NULL )
    {}


    /**  Ctor.
     *   Creates the window object for the game and initializes it.
     */
    Application::Application( int argc, char* argv[] ) :
        window_( new Window( 0.0f, 0.0f, 0.0f ) ),
        input_( window_ ),
        world_( NULL ),
        mesh_( NULL ),
        argc_( argc ),
        argv_( argv )
    {

        start_up();

        if( window_->ready() )
        {
#ifdef DEBUG
            fprintf( stderr, "Window created successfully.\n" );
#endif


#ifdef DEBUG
            //The following... should all be removed later...
            glPointSize(40.0f);
#endif




            Model::SG_Setup* sg = new Model::SG_Setup;

            sg->position( 0.0f, 0.0f, 0.0f );
            sg->eye_position( 2.0f, 1.75f, -2.0f );
            sg->target( 0.0f, 0.0f, 0.0f );
            sg->up_dir( 0.0f, 1.0f, 0.0f );
            sg->perspective( 45.0f, 1.0f, 5.0f );
            sg->window( window_ );

            world_ = Model::Scene_Graph::ctor( sg );

            delete sg;

            mesh_ = new Model::Mesh( window_, GL_TRIANGLES );


            fprintf( stderr, "Mesh addr: %lx\n", (unsigned long int) mesh_ );

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
            shader_->print_active_uniforms();


            world_->add_models( mesh_ );
            mesh_->set_shader( shader_ );


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
        world_->render();
        window_->swap();

        while( 1 )
        {
            input_.process();
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
