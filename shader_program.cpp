/**
 *  \author Thomas R. Carrel
 *  \file shader_program.cpp
 */

#include"shader_program.h"



/*
extern SHADER_TYPE_NAME SIMPLE_v;
extern SHADER_TYPE_NAME SIMPLE_f;
*/

#include "shader_externs.h"


/** Ctor.
 */
Shader::Shader( void )
{}






/** Dtor.
 *  Deletes the shader from the GPU's memory.
 */
Shader::~Shader( void )
{
    glDeleteProgram( program_ );
}





/**  Add pointers to the code for the current shader program.
 *  Since shader code is stored as a constant, this can be accomplished fairly
 *  easily.
 *
 * param code The address for the struct containing the code.
 * param type The type of shader being compiled (vertex, fragment, etc).
 */
void Shader::add_code( SHADER_TYPE_NAME* code, int type )
{
#ifdef DEBUG
    fprintf(
            stderr,
            "%s\n\n",
            code->code
           );
#endif

    switch( type )
    {
        case VERTEX_SHADER:
            code_.vertex    = &code->code;
            return;
        case TCS_SHADER:
            code_.tcs       = &code->code;
            return;
        case TEV_SHADER:
            code_.tev       = &code->code;
            return;
        case GEOMETRY_SHADER:
            code_.geometry  = &code->code;
            return;
        case FRAGMENT_SHADER:
            code_.fragment  = &code->code;
            return;
        case COMPUTE_SHADER:
            assert( false ); //Compute not implemented
            return;
    }
}




/**    Performs final compilation of the shader code on the GPU.  This must be
 *   done by the user, since it is unknown what shaders will be loaded.
 */
bool Shader::compile( void )
{

    shaders_.vertex    = glCreateShader( GL_VERTEX_SHADER );
    glShaderSource( shaders_.vertex, 1, &code_.vertex->code, NULL );
    glCompileShader( shaders_.vertex );

    shaders_.fragment  = glCreateShader( GL_FRAGMENT_SHADER );
    glShaderSource( shaders_.fragment, 1, &code_.fragment->code, NULL );
    glCompileShader( shaders_.fragment );

    if( link() )
    {
        printf( "<Shader::compile (from link())> Error occurred when" );
        printf( "linking.\n" );
        return ERROR;
    }

    return !ERROR;
}

//TODO: Add additional error checking and debugging capabilities.
//
//Linker for shader programs.
//
bool Shader::link()
{
    program_ = glCreateProgram();
    glAttachShader( program_, shaders_.vertex );
    glAttachShader( program_, shaders_.fragment );

    glLinkProgram( program_ );

    return !ERROR;
}
