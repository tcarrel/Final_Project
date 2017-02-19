



#ifndef  _COMMAND_H_
# define _COMMAND_H_

namespace Input
{
    /**
     * Virtual interface for all commands.
     */
    class Command
    {
        public:
            /** Dtor
             */
            virtual ~Command( void ) {}
            /** Execute the command.
             */
            virtual void execute( void ) = 0;
    };
} //Input namespace.

#endif
