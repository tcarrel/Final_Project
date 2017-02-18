/**
 * \file model.h
 * \author Thomas R. Carrel
 *
 * \brief Model class declaration.
 */


#ifndef  MODEL_H
# define MODEL_H



#include<GL/glew.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_opengl.h>

#include<GL/glu.h>
#include<GL/freeglut.h>

#include<stdio.h>



#include "../constants.h"
#include "../shader_program.h"

class Mesh;
class Shader;


/**
 * The class for a single model, eventually these will be able to contain
 * multiple meshes that are to be transformed as one unit.  This may also
 * end up as a node in the scene graph.
 */
class Model
{
    public:
        Model( void );
        ~Model( void );


        bool render( void );

        void set_program( Shader* );

    private:
        Mesh* mesh_;
        //Program
        Shader* program_;
};

#endif
