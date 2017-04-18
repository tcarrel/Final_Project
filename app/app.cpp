/**
 * \file app.cpp
 * \author Thomas R. Carrel
 *
 * \brief Application framework definition.
 */

#include "app.h"
#include "window.h"

#include "../colors.h"

#include "../model/sg_setup.h"
#include "../model/mesh.h"
#include "../model/model.h"

#include "../model/obj_loader/obj.h"
#include "../model/obj_loader/world_loader.h"

#include "../model/scene_graph.h"

#define GLM_INCLUDED //From window.h
#include "../helper_functions.h"
#undef  GLM_INCLUDED


namespace App
{

    /**  Generic Ctor.
     *   Creates the window object for the game and initializes it.
     */
    /*
    Application::Application( void ) :
        Application( (int) 1, (char**) NULL )
    {}
    */


    /**  Ctor.
     * Creates the window object for the game and initializes it, this version
     * of the ctor allows command line arguments to be passed in from main.  At
     * this point this does nothing different compared to the generic ctor as
     * there are no command line options that any part of the program needs to
     * be aware of, yet.
     * @param argv argv taken from the command line.
     */
    Application::Application( std::vector<std::string*>& argv ) :
        window_( new Window( to_vec_color( Color::GUNMETAL ) ) ),
        shader_( NULL ),
        input_( window_ ),
        world_( NULL ),
        mesh_( NULL )
    {
        argv_.swap( argv );
        start_up();

        if( window_->ready() )
        {

#ifdef DEBUG
            fprintf(
                    stderr,
                    "Window created successfully.\nAspect Ratio\t=\t%f\n",
                    window_->aspect() );
#endif
            parse_args();

            Model::SG_Setup* sg = new Model::SG_Setup;

            sg->position(        0.0f,  0.0f,  0.0f );
            sg->eye_position(    1.7f,  .75f, -1.7f );
            sg->target(          0.0f,  0.0f,  0.0f );
            sg->up_dir(          0.0f,  1.0f,  0.0f );
            sg->perspective(    45.0f,  1.0f, 30.0f, window_->aspect() );
            sg->window(         window_ );

            world_ = Model::Scene_Graph::ctor( sg );
            Model::OBJ::World_Loader loader( world_ );

            delete sg;
            sg = NULL;

            loader( "resource", "load_list", false );
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
            shader_->delete_this();
        }

        if( window_ )
        {
            delete window_;
        }

        SDL_Quit();
    }





    void Application::parse_args( void )
    {

        for( unsigned i = 1; i < argv_.size(); i++ )
        {
            if( *argv_[i] == "--help" )
            {
                command_line_help();
            }

            //Render as wireframe.
            else if( *argv_[i] == "--wf" )
            {
                fprintf(
                        stderr,
                        "\"%s\" ",
                        argv_[i]->c_str() );
                window_->set_wireframe_front();
            }
            else if( *argv_[i] == "--wf=1" )
            {
                fprintf(
                        stderr,
                        "\"%s\" ",
                        argv_[i]->c_str() );
                window_->set_wireframe_front();
            }
            else if( *argv_[i] == "--wf=on" )
            {
                fprintf(
                        stderr,
                        "\"%s\" ",
                        argv_[i]->c_str() );
                window_->set_wireframe_front();
            }

            //Render as wireframe with back facing edges shown.
            else if( *argv_[i] == "--wf=2" )
            {
                fprintf(
                        stderr,
                        "\"%s\" ",
                        argv_[i]->c_str() );
                window_->set_wireframe_full();
            }
            else if( *argv_[i] == "--wf=full" )
            {
                fprintf(
                        stderr,
                        "\"%s\" ",
                        argv_[i]->c_str() );
                window_->set_wireframe_full();
            }


            //Normal rendering mode.
            else if( *argv_[i] == "--wf=0" )
            {
                fprintf(
                        stderr,
                        "\"%s\" ",
                        argv_[i]->c_str() );
                window_->set_wireframe_off();
            }
            else if( *argv_[i] == "--wf=off" )
            {
                fprintf(
                        stderr,
                        "\"%s\" ",
                        argv_[i]->c_str() );
                window_->set_wireframe_off();
            }

            //No longer needed after this.
            delete argv_[i];
            argv_[i] = NULL;
        }

#ifdef CLEAR_ARGS
        //  Command line args are no longer needed in memory because at this
        //point all necessary changes have been made to account for them,
        //however, if they are still needed by the main program, compiler
        //-D CLEAR_ARGS can be used during compilation to keep them persistent
        //after they've been processed.
        auto iter = argv_.begin();
        while( *iter != NULL )
        {
            ++iter;
        }
        argv_.erase( iter, argv_.end() );
#endif
    }





    void Application::command_line_help( void )
    {
        const std::string& CMD = *argv_[0];

        printf( bold("Command line options for %s:\n\n").c_str(), CMD.c_str() );
        printf( "\t--help\t\tShow this message.\n\n" );
        printf( "\t--wf\t\tSet partial wireframe rendering mode.  Only the edg"
                "es of\n");
        printf( "\t--wf=1\t\tfront facing polygons will be rendered.\n" );
        printf( "\t--wf=on\n\n" );
        printf( "\t--wf=2\t\tSet full wireframe rendering mode.  All faces wil"
                "l be\n");
        printf( "\t--wf=full\trendered.\n\n" );
        printf( "\t--wf=0\t\tDefault rendering mode.  This is the default rend"
                "ering mode.\n" );
        printf( "\t--wf=off\n\n" );
        fflush( stdout );

        exit(0);
    }
} //App namespace.

