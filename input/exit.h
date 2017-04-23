/**
 *
 * \file exit.h
 * \author Thomas R. Carrel
 *
 * \brief The command to quit the game.
 */



#include<stdlib.h>

#include "command.h"
#include "command_enum.h"

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
            Exit_Command( bool* q )
            { quit_ = q; } 

            void execute( void* )
            { execute(); }

            void execute( void )
            { *quit_ = true; }

        private:
            static const Commands_Enum TYPE = EXIT_COMMAND;

            bool* quit_;
    };

}

#endif
