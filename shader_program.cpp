/**
 *  \author Thomas R. Carrel
 *  \file shader_program.cpp
 *
 *  \brief Provides definitions for the Shader class.
 */

#include"shader_program.h"

#include "shader_externs.h"







/**
 *   Tracks the current shader program used for rendering.  This is used to
 * minimize the number of calls to glUseProgram().
 */
GLuint Shader::current_program_(UINT_MAX);





/** Ctor.
 */
Shader::Shader( void ) 
{
//    current_program_ = UINT_MAX;
}






/** Dtor.
 *  Deletes the shader from the GPU's memory.
 */
Shader::~Shader( void )
{
    // Do not delete these explicitly.
    code_.vertex = NULL;
    code_.tcs = NULL;
    code_.tev = NULL;
    code_.geometry = NULL;
    code_.fragment = NULL;

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
#ifdef DEBUG_SHADER_PROG
    fprintf(
            stderr,
            "%s\n\n",
            *code
           );
#endif

    switch( type )
    {
        case VERTEX_SHADER:
            code_.vertex    = code->code;
            ids_.vertex     = code->id;
            return;
        case TCS_SHADER:
            code_.tcs       = code->code;
            ids_.tcs        = code->id;
            return;
        case TEV_SHADER:
            code_.tev       = code->code;
            ids_.tev        = code->id;
            return;
        case GEOMETRY_SHADER:
            code_.geometry  = code->code;
            ids_.geometry   = code->id;
            return;
        case FRAGMENT_SHADER:
            code_.fragment  = code->code;
            ids_.fragment   = code->id;
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
    if( !(code_.vertex || code_.fragment) )
    {
        printf( "Missing shaders." );
        return ERROR;
    }

    shaders_.vertex    = glCreateShader( GL_VERTEX_SHADER );
    glShaderSource( shaders_.vertex, 1, &code_.vertex, NULL );
    glCompileShader( shaders_.vertex );

    if( code_.tcs )
    {
        shaders_.tcs       = glCreateShader( GL_TESS_CONTROL_SHADER );
        glShaderSource( shaders_.tcs, 1, &code_.tcs, NULL );
        glCompileShader( shaders_.tcs );
    }

    if( code_.tev )
    {
        shaders_.tev        = glCreateShader( GL_TESS_EVALUATION_SHADER );
        glShaderSource( shaders_.tev, 1, &code_.tev, NULL );
        glCompileShader( shaders_.tev );
    }

    if( code_.geometry )
    {
        shaders_.geometry   = glCreateShader( GL_GEOMETRY_SHADER );
        glShaderSource( shaders_.geometry, 1, &code_.geometry, NULL );
        glCompileShader( shaders_.geometry );
    }

    shaders_.fragment  = glCreateShader( GL_FRAGMENT_SHADER );
    glShaderSource( shaders_.fragment, 1, &code_.fragment, NULL );
    glCompileShader( shaders_.fragment );

    if( link() == ERROR )
    {
        printf( "<Shader::compile (from link())> Error occurred when" );
        printf( " linking.\n" );
        return ERROR;
    }

    return !ERROR;
}






/** Calls glUseProgram, if necessary.
 * Calls to glUseProgram are expensive and to be avoided, if possible.
 */
void Shader::use_program( void )
{
    if( current_program_ != program_ )
    {
        glUseProgram( program_ );
        current_program_ = program_;
    }
}








/** \todo Add additional error checking and debugging capabilities.
 *
 * Linker for shader programs.
 */
bool Shader::link()
{
#ifdef DEBUG
#endif

    program_ = glCreateProgram();
    glAttachShader( program_, shaders_.vertex );

    if( code_.tcs )
    {
        glAttachShader( program_, shaders_.tcs );
    }

    if( code_.tev )
    {
        glAttachShader( program_, shaders_.tev );
    }

    if( code_.geometry )
    {
        glAttachShader( program_, shaders_.geometry );
    }

    glAttachShader( program_, shaders_.fragment );

    glLinkProgram( program_ );

    // No longer needed in GPU RAM.
    glDeleteShader( shaders_.vertex );
    if( code_.tcs )
    {
        glDeleteShader( shaders_.tcs );
    }
    if( code_.tev )
    {
        glDeleteShader( shaders_.tev );
    }
    if( code_.geometry )
    {
        glDeleteShader( shaders_.geometry );
    }
    glDeleteShader( shaders_.fragment );



    if( current_program_ == UINT_MAX )
    {
        use_program();
    }

    return !ERROR;
}




/**
 * Check if this shader is equivilant to another one.
 * If there is time later, this will allow for some memory optimization.
 */
bool Shader::operator==( Shader& rhs )
{
    if( this->ids_.vertex != rhs.ids_.vertex )
    {
        return false;
    }

    if( this->ids_.tcs != rhs.ids_.tcs )
    {
        return false;
    }

    if( this->ids_.tev != rhs.ids_.tev )
    {
        return false;
    }

    if( this->ids_.geometry != rhs.ids_.geometry )
    {
        return false;
    }

    if( this->ids_.fragment != rhs.ids_.fragment )
    {
        return false;
    }

    return true;
}






/** Prints shader contents.
 * Really just for debugging purposes.
 */
void Shader::print( void )
{
    const char format[] = "%s:\n\n%s\n\n";

    printf( "==Shader Text=====================\n" );
    printf( "Shader id: <%i.%i.%i.%i.%i>\n\n",
            ids_.vertex,
            ids_.tcs,
            ids_.tev,
            ids_.geometry,
            ids_.fragment );

    if( code_.vertex )
    {
        printf( format,
                "Vertex",
                code_.vertex );
    }

    if( code_.tcs )
    {
        printf( format,
                "Tesselation Control",
                code_.tcs );
    }

    if( code_.tev )
    {
        printf( format,
                "Tesselation Evaluation",
                code_.tev );
    }

    if( code_.geometry )
    {
        printf( format,
                "Geometry",
                code_.geometry );
    }

    if( code_.fragment )
    {
        printf( format,
                "Fragment",
                code_.fragment );
    }

    printf( "==End of Shader===============\n\n" );
}



