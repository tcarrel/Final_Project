/**
 * \file app.cpp
 * \author Thomas R. Carrel
 *
 * \brief Application framework definition.
 */

#include "app.h"
#include "window.h"

#include "../colors.h"

#include "../model/scene_graph.h"
#include "../model/sg_setup.h"
#include "../model/mesh.h"
#include "../model/model.h"

#include "../model/obj_loader/obj.h"

#include "../helper_functions.h"



namespace App
{

    /**  Generic Ctor.
     *   Creates the window object for the game and initializes it.
     */
    Application::Application( void ) :
        Application( (int) 1, (char**) NULL )
    {}


    /**  Ctor.
     *   Creates the window object for the game and initializes it, this
     *   version of the ctor allows command line arguments to be passed in from
     *   main.  At this point this does nothing different compared to the
     *   Generic ctor as there are no command line options that any part of
     *   the program needs to be aware of, yet.
     *   \param argc argc taken from the command line.
     *   \param argv argv taken from the command line.
     */
    Application::Application( int argc, char** argv ) :
        window_( new Window( to_vec_color( Color::DARK_GUNMETAL ) ) ),
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
            sg->perspective( 45.0f, 1.0f, 5.0f, window_->aspect() );
            sg->window( window_ );

            world_ = Model::Scene_Graph::ctor( sg );

            delete sg;
            sg = NULL;

            Model::OBJ::OBJ_File loader;
            loader.trace( "_obj_trace" );

            shader_ = new Shader;
            shader_->add_code( &SIMPLE_v, VERTEX_SHADER   );
            shader_->add_code( &SIMPLE_f, FRAGMENT_SHADER );

            if( shader_->compile() == ERROR )
            {
                fprintf(
                        stderr,
                        "Could not compile shaders.\n\n"
                       );

            }

            mesh_ = loader.load_file( "resource/cube.obj", shader_, true, 1.0f );
            /*
            fprintf( stderr, "Mesh::\naddr:\t0x%Lx\nname:\t%s\n",
                    (long long int) mesh_,
                    mesh_->name().c_str() );
                    */
            mesh_->print_info();
            loader.stop_trace();

            shader_->print();
            shader_->print_active_uniforms();

            world_->add_models( mesh_ );
//            mesh_->set_shader( shader_ );

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
            fprintf( stderr, "Initializing window.\n" );
            window_->init();
        }
    }





    /**  Game main loop.
     *     This contains the main loop of the game as well as performing the
     *   final bit of initialization before the loop begins.
     */
    int Application::run( void )
    {
        assert( world_ != NULL );
        world_->render();

        while( input_.process() )
        {}

        return 0;
    }





    /**  Dtor.
     *     Resposible for all de-initialization and cleanup.
     */
    Application::~Application( void )
    {
        if( world_ )
        {
            delete world_;
        }

        if( shader_ )
        {
            delete shader_;
        }

        if( window_ )
        {
            delete window_;
        }

        SDL_Quit();
    }

} //App namespace.
