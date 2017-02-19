/**
 *
 * \file input_handler.cpp
 * \author Thomas R. Carrel
 *
 * \brief Input_Handler class definitions.
 */



#include "input_handler.h"

namespace Input
{

    Input_Handler::Input_Handler( App::Window* w )
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

        com_[WINDOW_SHOW_COMMAND] = new Window_Redraw( w );
        com_[EXIT_COMMAND] = new Exit_Command;
    }



    Input_Handler::~Input_Handler( void )
    {
        for( int i = 0; i < ALL_COMMANDS; i++ )
        {
            delete com_[i];
        }
    }



    /** Process all commands until the event queue is empty.
     */
    void Input_Handler::process( void )
    {
        while( SDL_PollEvent( &q_ ) != 0 )
        {
            switch( q_.type )
            {
                case SDL_QUIT:
                    com_[EXIT_COMMAND]->execute();
                    break;
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
                            com_[WINDOW_SHOW_COMMAND]->execute();
                            break;
                        default:
                            ;
                    }
                    break;
                case SDL_KEYUP:
                    switch( q_.key.keysym.sym )
                    {
                        case SDLK_F12:
                            com_[EXIT_COMMAND]->execute();
                            break;
                        default:
                            ;
                    }
                    break;
                case SDL_KEYDOWN:

                    break;
                default:
                    ;
            }
        }
    }

} // Input namespace.
