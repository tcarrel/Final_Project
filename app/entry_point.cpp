/**
 * \file entry_point.cpp
 * \author Thomas R. Carrel
 *
 * \brief Program entry point.
 */





#include "app.h"



/**  The entry point for the game.
*/
int main( int argc, char* argv[] )
{
    if( argc > 1 )
    {
        App::Application app(argc, argv);
        app.run();
    }
    else
    {
        App::Application app;
        app.run();
    }

    return 0;
}
