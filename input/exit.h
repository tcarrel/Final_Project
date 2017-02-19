



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
            virtual void execute()
            { exit( 0 ); }
    };

}

#endif
