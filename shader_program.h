/**
 *  \author Thomas R. Carrel
 *  \file shader_program.h
 */


#ifndef  __SHADER_PROGRAM_H__
# define __SHADER_PROGRAM_H__

#include<GL/glew.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_opengl.h>

#include<GL/glu.h>
#include<GL/freeglut.h>

#include<cassert>


#include "constants.h"
#include "shaders.h"



/**  A wraper class for a shader program.
 */
class Shader
{
    public:
        Shader( void );
        ~Shader(void );
        
        bool compile( void );
        const GLuint& get( void ) { return program_; }

        bool operator==( Shader& );

        void print( void ); 

        void add_code( SHADER_TYPE_NAME*, int );

    private:

        bool link( void ); ///< Called by compile().
        //bool load_source( string, GLGLchar*, string );

        struct 
        {
            GLchar* vertex      = NULL;
            GLchar* tcs         = NULL;
            GLchar* tev         = NULL;
            GLchar* geometry    = NULL;
            GLchar* fragment    = NULL;
        } code_; ///<  Pointers to the source code for the various shaders.

        struct
        {
            GLuint  vertex      = 0;
            GLuint  tcs         = 0;
            GLuint  tev         = 0;
            GLuint  geometry    = 0;
            GLuint  fragment    = 0;
        } ids_;

        struct 
        {
            GLuint  vertex;
            GLuint  tcs;
            GLuint  tev;
            GLuint  geometry;
            GLuint  fragment;
        } shaders_; ///< The location of the shaders in the GPU's memory.

        GLuint      program_; ///<   The handle for the shader program after
        ///< it's been compiled.
        bool        ready_; ///<   Flag indicating the shader has been compiled
        ///< and is ready for use.
};

#endif
