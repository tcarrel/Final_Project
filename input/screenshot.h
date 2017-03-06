/**
 *
 * \file screenshot.h
 * \author Thomas R. Carrel
 *
 * \brief A Command class for taking screenshots.
 *
 */


#include "command.h"
#include "command_enum.h"

#include "../app/window.h"

#include<ctime>
#include<string>
#include<cctype>

#include<cstdio>


#include<SOIL/SOIL.h>

#ifndef  _SCREENSHOT_H_
# define _SCREENSHOT_H_

namespace Input
{


    /** For taking screenshots.
     */
    class Screenshot_Command : public Command
    {
        public:
            /** Ctor
             * \param w The current window.  Used to determine the necessary
             * image dimensions.
             */
            Screenshot_Command( App::Window* w ) :
                w_( w->w() ), h_( w->h() ) {}

            /** Nothing is needed to be passed into this command, so it just
             * calls the version of the same function that takes no arguments.
             */
            void execute( void* )
            { execute(); }

            /** Saves a screenshot in bmp format in the Screenshots sub
             * directory.  The filename is the word 'Screenshot' followed by
             * the current date and time.
             */
            void execute( void )
            {
                time_t raw_time;
                struct tm* time_info;

                time( &raw_time );
                time_info = localtime( &raw_time );
                std::string filename = string( asctime( time_info ) );
                filename = "Screenshots/Screenshot " + filename + ".bmp";

                for( auto i = filename.begin(); i != filename.end(); i++ )
                {
                    if( *i < 31 )
                    {
                        filename.erase( i );
                        continue;
                    }

                    if( isspace( *i ) )
                    {
                        *i = '_';
                        continue;
                    }

                    if( *i == ':' )
                    {
                        *i = '-';
                    }
                }

                bool status = SOIL_save_screenshot
                    (
                     filename.c_str(),
                     SOIL_SAVE_TYPE_BMP,
                     0, 0, w_, h_
                    );

                if( !status )
                {
                    fprintf( 
                            stderr,
                            "Screenshot failed.\n"
                           );
                }
            }

        private:
            /** For debugging.
             */
            static const Commands_Enum TYPE = SCREENSHOT_COMMAND;

            unsigned w_; ///< Window width.
            unsigned h_; ///< Window height.
    };

} //Input namespace.

#endif
