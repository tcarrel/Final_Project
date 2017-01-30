//
//  Thomas Russel Carre
//
//  shader_program.h
//


#ifndef __SHADER_PROGRAM_H__
# define __SHADER_PROGRAM_H__

#include<GL/glew.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_opengl.h>

#include<GL/glu.h>
#include<GL/freeglut.h>

//For file loading and string manipulation;
#include<iostream>
using std::string;
#include<fstream>
using std::ifstream;

#include<cctype>


#include"constants.h"
#include"shaders.h"

class Shader
{
    public:
        Shader( void );
        ~Shader(void );
        
        bool compile( const char*, const char* );
        const GLuint& get( void ) { return program_; }
      
    private:

        bool link( void ); ///< Called by compile().
        //bool load_source( string, GLchar*, string );

        /*
        struct Files
        {
            GLchar* vertex_     = NULL;
            GLchar* tcs_        = NULL;
            GLchar* tev_        = NULL;
            GLchar* geometry_   = NULL;
            GLchar* fragment_   = NULL;
        };
        */

        struct Shaders
        {
            GLuint  vertex_;
            GLuint  fragment_;
        };

        GLuint      program_;
        bool        ready_;
};

#endif
