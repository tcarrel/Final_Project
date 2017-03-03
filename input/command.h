/**
 *
 * \file command.h
 * \author Thomas R. Carrel
 *
 * \brief This is the base class that all commands must inherit from.  It is
 * simply a virtual interface for all the other commands.  The interface for
 * this program uses the Command pattern because it allows the end user to
 * customize their controls and because in its eventual form, will allow for
 * commands to be received from sources other than the player.  For example,
 * from an AI class or over a network for some version of multiplayer.
 */



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
            virtual void execute( void* )   = 0;
            virtual void execute( void )    = 0;
    };
} //Input namespace.

#endif
