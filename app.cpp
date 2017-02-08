/**
 * \file app.cpp
 * \author Thomas R. Carrel
 */

#include "app.h"



/*
extern SHADER_TYPE_NAME SIMPLE_v;
extern SHADER_TYPE_NAME SIMPLE_f;
*/

#include "shader_externs.h"



/**  Ctor.
 *   Creates the window object for the game and initializes it.
 */
Application::Application( void ) :
    window_( new Window(0.5f, 0.5f, 0.5f, 1.0f) )
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
    
    shader_ = new Shader;
    shader_->add_code( &SIMPLE_v, VERTEX_SHADER );
    shader_->add_code( &SIMPLE_f, FRAGMENT_SHADER );
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

    if( shader_ )
        delete shader_;
}

