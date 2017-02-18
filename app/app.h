/**
 * \file app.h
 * \author Thomas R. Carrel
 *
 * \brief Application framework (Application class) declaration.
 */

#ifndef  APPLICATION_H
# define APPLICATION_H

#include<GL/glew.h>

#include<SDL2/SDL.h>
#include<SDL2/SDL_opengl.h>

#include<GL/glu.h>
#include<GL/freeglut.h>

#include "../constants.h"
#include "../shader_program.h"
#include "../shaders.h"

#include "window.h"

#include<stdio.h>

class Mesh;

/**  The main game object.
 */
class Application
{
    public:
        Application( void );
        ~Application(void );

       int run( void ); 
    private:

       void start_up( void );

       Window*  window_; ///< The window object that the game will be
                         ///< displayed in.

       Shader* shader_;

       Mesh* mesh_;
       //Model* models_;
};

#endif
