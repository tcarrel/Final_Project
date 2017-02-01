

#include"app.h"


/**  Ctor.
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



void Application::start_up( void )
{
    SDL_Init( SDLSYSTEMS );
    window_->init();
}



int Application::run( void )
{
    SDL_Delay(3000);

    return 0;
}









Application::~Application( void )
{
    SDL_Quit();
}

