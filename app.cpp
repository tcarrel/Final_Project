/**
 * \file app.cpp
 * \author Thomas R. Carrel
 */

#include"app.h"


/**  Ctor.
 *   Creates the window object for the game and initializes it.
 */
Application::Application( void ) :
    window_( new Window )
{

    start_up();

    if( window_->good() )
        fprintf( stderr, "Window created successfully.\n" );
    else
        fprintf( stderr, "Failed to create window.\n" );
}



/**  Initializes SDL2 and the window object.
 */
void Application::start_up( void )
{
    SDL_Init( SDLSYSTEMS );
    window_->init();
}



/**  Game main loop.
 *     This contains the main loop of the game as well as performing the final
 *   bit of initialization before the loop begins.
 */
int Application::run( void )
{
    SDL_Delay(3000);

    return 0;
}







/**  Dtor.
 *     Resposible for all de-initialization and cleanup.
 */
Application::~Application( void )
{
    SDL_Quit();
}

