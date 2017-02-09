/**
 * \file model.h
 * \author Thomas R. Carrel
 */


#ifndef  MODEL_H
# define MODEL_H



#include<GL/glew.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_opengl.h>

#include<GL/glu.h>
#include<GL/freeglut.h>

#include<stdio.h>



#include "constants.h"
#include "shader_program.h"

class Shader;

class Model
{
    public:
        Model( void );
        ~Model( void );

        bool render( void );

    private:
        //static Mesh
        //Program
        Shader* program_;
};

#endif
