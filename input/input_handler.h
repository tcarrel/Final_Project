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

#include "../app/window.h"

#include "all_commands.h"

#ifndef  _INPUT_HANDLER_H_
# define _INPUT_HANDLER_H_

/** Inted to make the Input_Handler simpler, but this doesn't particularly work
 * very well with the SDL2 event handler.
 */
# define NUM_EVENT_SOURCES (15)

namespace Input
{

    /**A wrapper around the SDL Event Queue.
     */
    class Input_Handler
    {
        public:
            Input_Handler( App::Window* );
            ~Input_Handler( void );

            void process( void );

        private:
            unsigned get_index( void );


            SDL_Event q_;

            Command* com_[NUM_EVENT_SOURCES];
            
//            Command* exit_;
    };
} //Input namespace.

#endif
