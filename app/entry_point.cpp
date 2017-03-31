/**
 * \file entry_point.cpp
 * \author Thomas R. Carrel
 *
 * \brief Program entry point.
 */





#include "app.h"

#include<string>
#include<vector>



/**  The entry point for the game.
*/
int main( int argc, char* argv[] )
{
    std::vector<std::string*> args;
    for( int i = 0; i < argc; i++ )
    {
        args.push_back( new string(argv[i]) );
    }

    App::Application app(args);
    app.run();

    return 0;
}
