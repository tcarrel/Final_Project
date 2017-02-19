/**
 *
 * \file input_handler.h
 * \author Thomas R. Carrel
 *
 * \brief Input_Handler class declaration.
 *
 */



#include<GL/glew.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_opengl.h>

#include<GL/glu.h>
#include<GL/freeglut.h>

#include "../app/window.h"

#include "all_commands.h"

#ifndef  _INPUT_HANDLER_H_
# define _INPUT_HANDLER_H_

namespace Input
{
    /** An enumeration representing all possible commands.
     */
    enum Commands_Enum{
        WINDOW_SHOW_COMMAND, ///< Window given focus.
        EXIT_COMMAND, ///< Exit 
        ALL_COMMANDS  ///< Qty
    };

    /**A wrapper around the SDL Event Queue.
     */
    class Input_Handler
    {
        public:
            Input_Handler( App::Window* );
            ~Input_Handler( void );

            void process( void );

        private:
            SDL_Event q_;

            Command* com_[ALL_COMMANDS];
    };
} //Input namespace.

#endif
