/**
 *
 * @file input_handler.cpp
 * @author Thomas R. Carrel
 *
 * @brief Input_Handler class definitions.
 */


#ifdef IH_DEBUG
# include<cstdio>
#endif

#include "input_handler.h"

namespace Input
{

    /** Ctor.
     * @param w The window that the app is running in.
     * @param q A pointer to the boolean variable used to exit the game loop.
     */
    Input_Handler::Input_Handler( App::Window* w, bool* q )
    {
        uint32_t init = SDL_WasInit( SDL_INIT_EVERYTHING );
        if( !(init & SDL_INIT_EVENTS) )
        {
            SDL_InitSubSystem( SDL_INIT_EVENTS );
        }
        if( !(init & SDL_INIT_JOYSTICK) )
        {
            SDL_InitSubSystem( SDL_INIT_JOYSTICK );
        }
        if( !(init & SDL_INIT_GAMECONTROLLER ) )
        {
            SDL_InitSubSystem( SDL_INIT_GAMECONTROLLER );
        }

        for( unsigned i = 0; i < NUM_EVENT_SOURCES; i++ )
        {
            com_[i] = Null_Command::instance();
#ifdef IH_DEBUG
            fprintf( stderr, "com_[%i] = %li [null]\n", i, (long) com_[i] );
#endif
        }

        com_[ WINDOW_SHOW_COMMAND ] = new Window_Redraw( w );
        com_[ SCREENSHOT_COMMAND ] = new Screenshot_Command( w );
        com_[ EXIT_COMMAND ] = new Exit_Command( q );

    }



    /** Dtor.
     */
    Input_Handler::~Input_Handler( void )
    {
        for( int i = 0; i < NUM_EVENT_SOURCES; i++ )
        {
            if( com_[i] != Null_Command::instance() )
            {
                delete com_[i];
            }
            else
            {
                com_[i] = NULL;
            }
        }
        //Null_Command::deinstance();
    }



    /** Process all commands until the event queue is empty.
    */
    bool Input_Handler::process( void )
    {
        while( SDL_PollEvent( &q_ ) != 0 )
        {
            unsigned i = get_index();
#ifdef IH_DEBUG
            fprintf( stderr,
                    "EXIT %i\n"
                    "WINDOW %i\n"
                    "NULL %i\n"
                    "SCREENSHOT %i\n"
                    "ALL %i\n",
                    EXIT_COMMAND,
                    WINDOW_SHOW_COMMAND,
                    NULL_COMMAND,
                    SCREENSHOT_COMMAND,
                    ALL_COMMANDS );
            fprintf( stderr, "Index %i/%i\n", i, NUM_EVENT_SOURCES );
            fflush( stderr );
#endif
            /*
               if( i == EXIT_COMMAND )
               {
               return false;
               }
               */

            com_[i]->execute();
        }
        return true;
    }



    unsigned Input_Handler::get_index(  )
    {
        switch( q_.type )
        {
            case SDL_QUIT:
                return EXIT_COMMAND;
            case SDL_WINDOWEVENT:
                switch( q_.window.event )
                {
                    case SDL_WINDOWEVENT_RESTORED:
                        //Fallthrough.
                    case SDL_WINDOWEVENT_FOCUS_GAINED:
                        //Fallthrough.
                    case SDL_WINDOWEVENT_SHOWN:
                        //Fallthrough.
                    case SDL_WINDOWEVENT_EXPOSED:
                        return WINDOW_SHOW_COMMAND;
                    default:
                        return ALL_COMMANDS;
                }
                break;
            case SDL_KEYUP:
                switch( q_.key.keysym.sym )
                {
                    case SDLK_F12:
                        return EXIT_COMMAND;
                    case SDLK_F8:
                        //case SDLK_PRINTSCREEN:
                        return SCREENSHOT_COMMAND;
                    default:
                        return ALL_COMMANDS;
                }
                break;
            case SDL_KEYDOWN:
                return ALL_COMMANDS;
            default:
                return ALL_COMMANDS;
        }
    }

} // Input namespace.
