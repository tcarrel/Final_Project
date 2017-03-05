/**
 *
 * \file null.h
 * \author Thomas R. Carrel
 *
 * \brief A command that does nothing.  This is setup like a singleton.
 *
 */

#include "command.h"
#include "command_enum.h"

#ifndef  _NULL_COMMAND_H_
# define _NULL_COMMAND_H_

namespace Input
{

    /**
     * Null command
     */
    class Null_Command : public Command
    {
        public:
            /** Dtor
             */
            ~Null_Command( void ) { deinstance(); }

            /** Do nothing.
             */
            void execute( void* )
            {
//                asm volatile( "" : "+g"(x));
            }

            /** Do nothing.
            */
            void execute( void )
            {
                /*
                int x = 0;
                asm volatile( "" : "+g"(x));
                */
            }

            /** Return the Null_Command, if necessary, create it.
            */
            static Command* instance( void );

            /** Destroy the Null_Command object, if it exists.
            */
            static void deinstance( void );
        private:
            /** Private ctor.
            */
            Null_Command() {}

            /** Store the address of the existing instance of the Null_Command.
            */
            static Command* instance_;

            static const Commands_Enum TYPE = NULL_COMMAND;
    };

}

#endif
