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

#include<cassert>


#include"constants.h"
#include"shaders.h"



class Shader
{
    public:
        Shader( void );
        ~Shader(void );
        
        bool compile( const char*, const char* );
        const GLuint& get( void ) { return program_; }


        void add_code( SHADER_TYPE_NAME* s, int type );
      
    private:

        bool link( void ); ///< Called by compile().
        //bool load_source( string, GLchar*, string );

        struct 
        {
            SHADER_TYPE_NAME* vertex      = NULL;
            SHADER_TYPE_NAME* tcs         = NULL;
            SHADER_TYPE_NAME* tev         = NULL;
            SHADER_TYPE_NAME* geometry    = NULL;
            SHADER_TYPE_NAME* fragment    = NULL;
        } code_;

        struct 
        {
            GLuint  vertex;
            GLuint  fragment;
        } shaders_;

        GLuint      program_;
        bool        ready_;
};

#endif
