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

#include<string>

#define GLM_INCLUDED //From window.h
#include "../helper_functions.h"
#undef  GLM_INCLUDED


namespace App
{


    void unrecognized_command( const string& st )
    {
                fprintf(
                        stderr,
                        "%s Argument < %s > not recognized, ignoring.\n",
                        red( "WARNING:" ).c_str(),
                        st.c_str() );
    }

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
        window_( new Window( to_vec_color( Color::COPPER_ROSE ) ) ),
        shader_( NULL ),
        input_( window_ ),
        world_( NULL ),
        mesh_( NULL ),
        wireframe_( false ),
        deg_per_sec_( NULL ),
        level_filename_( NULL )
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

            Model::OBJ::World_Loader loader( window_ );

            if( level_filename_ )
            {
                loader( "resource", *level_filename_, world_, false );
            }
            else
            {
                loader( "resource", world_, false );
            }

            if( !world_ )
            {
                fprintf(
                        stderr,
                        "Failed to initialize scene graph."
                       );
                exit(1);
            }

            if( wireframe_ )
            {
                world_->set_wireframe();
            }

            if( deg_per_sec_ )
            {
                world_->set_dps( *deg_per_sec_ );
                fprintf(
                        stderr,
                        "Rotation speed set to %f degrees per second.\n",
                        *deg_per_sec_ );
                delete deg_per_sec_;
                deg_per_sec_ = NULL;
            }
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

        while( input_.process() )
        {
            world_->render();
        }

        delete world_;
        world_ = NULL;

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

        for( auto iter = argv_.begin() + 1; iter != argv_.end(); iter++ )
        {
            string arg = **iter;

            if( arg == "--help" )
            {
                command_line_help();
            }

            if( arg[0] != '-' && arg[1] != '-' )
            {
                unrecognized_command( arg );

                delete *iter;
                *iter = NULL;

                continue;
            }

            //Render as wireframe.
            else if( arg == "--wf" )
            {
                fprintf(
                        stderr,
                        "\"%s\" ",
                        arg.c_str() );
                window_->set_wireframe_front();
                wireframe_ = true;
            }
            else if( arg == "--wf=1" )
            {
                fprintf(
                        stderr,
                        "\"%s\" ",
                        arg.c_str() );
                window_->set_wireframe_front();
                wireframe_ = true;
            }
            else if( arg == "--wf=on" )
            {
                fprintf(
                        stderr,
                        "\"%s\" ",
                        arg.c_str() );
                window_->set_wireframe_front();
                wireframe_ = true;
            }

            //Render as wireframe with back facing edges shown.
            else if( arg == "--wf=2" )
            {
                fprintf(
                        stderr,
                        "\"%s\" ",
                        arg.c_str() );
                window_->set_wireframe_full();
                wireframe_ = true;
            }
            else if( arg == "--wf=full" )
            {
                fprintf(
                        stderr,
                        "\"%s\" ",
                        arg.c_str() );
                window_->set_wireframe_full();
                wireframe_ = true;
            }


            //Normal rendering mode.
            else if( arg == "--wf=0" )
            {
                fprintf(
                        stderr,
                        "\"%s\" ",
                        arg.c_str() );
                window_->set_wireframe_off();
            }
            else if( arg == "--wf=off" )
            {
                fprintf(
                        stderr,
                        "\"%s\" ",
                        arg.c_str() );
                window_->set_wireframe_off();
            }

            if( arg == "--dps" )
            {
                deg_per_sec_ = new float( stof(**(iter + 1)) );
                argv_.erase(iter + 1);
            }

            if( arg == "--level" )
            {
                level_filename_ = new string( **( iter + 1 ) );
                argv_.erase(iter + 1);
            }

            /*
            //Begin more complicated parsing.
            auto equal_sign = argv_[i]->find_first_of("=");
            if( equal_sign != std::string::npos )
            {                
                string val  = argv_[i]->substr( equal_sign + 1 ),
                       comm = argv_[i]->substr( 0, equal_sign + 1 );
                if( comm == "--dps=" )
                {
                    deg_per_sec_ = new float( stof(val) );
                }
            }
            */

            //No longer needed after this.
            delete *iter;
            *iter = NULL;
        }

#ifdef CLEAR_ARGS
        //  Command line args are no longer needed in memory because at this
        //point all necessary changes should have been made to account for them,
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

