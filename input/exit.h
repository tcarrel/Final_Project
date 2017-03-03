/**
 *
 * \file exit.h
 * \author Thomas R. Carrel
 *
 * \brief The command to quit the game.
 */



#include<stdlib.h>

#include "command.h"

#ifndef  _EXIT_COMMAND_H_
# define _EXIT_COMMAND_H_

namespace Input
{

    /**
     * Quit.
     */
    class Exit_Command : public Command
    {
        public:
            void execute( void* )
            { execute(); }

            void execute( void )
            { exit(0); }
    };

}

#endif
