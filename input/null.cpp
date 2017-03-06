/**
 *
 * \file null.cpp
 * \author Thomas R. Carrel
 *
 * \brief Defines the Input Handler's Null Command.
 *
 */


#include<cstdlib>

#include "null.h"



namespace Input
{

    Command* Null_Command::instance_ = NULL;

    Command* Null_Command::instance( void )
    {
        if( !instance_ )
        {
            instance_ = new Null_Command;
        }
        return instance_;
    }

    void Null_Command::deinstance( void )
    {
        if( instance_ )
        {
            delete instance_;
            instance_ = NULL;
        }
    }

} //Input command.
