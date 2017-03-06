


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

    class Screenshot_Command : public Command
    {
        public:
            Screenshot_Command( App::Window* w ) :
                w_( w->w() ), h_( w->h() ) {}

            void execute( void* )
            { execute(); }

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
            static const Commands_Enum TYPE = SCREENSHOT_COMMAND;

            unsigned w_;
            unsigned h_;
    };

} //Input namespace.

#endif
