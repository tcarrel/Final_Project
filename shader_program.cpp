/**
 *  \author Thomas R. Carrel
 *  \file shader_program.cpp
 *
 *  \brief Provides definitions for the Shader class.
 */






#include "shader_program.h"
#include "shader_externs.h"

#include<sstream>
#include<climits>



//helper functions


/**  Converts and integer to a string.
 * \param i The integer.
 */
string numtoa( GLuint i )
{
    std::stringstream S;
    S << i;
    return S.str();
}




/**  Returns a string containing the name of the shader type.
 * \param s A value from the shader type enum (Shaders).
 */
string get_shader_type_string( Shaders s )
{
    switch( s )
    {
        case VERTEX_SHADER:
            return "vertex";
        case TCS_SHADER:
            return "tesselation control";
        case TEV_SHADER:
            return "tesselation evaluation";
        case GEOMETRY_SHADER:
            return "geometry";
        case FRAGMENT_SHADER:
                return "fragment";
        case COMPUTE_SHADER:
                return "compute";
        default:
                return "unkown shader type";
    }
}







/**
 *   Tracks the current shader program used for rendering.  This is used to
 * minimize the number of calls to glUseProgram().
 */
GLuint Shader::current_program_( 0 );





/** Ctor.
 */
Shader::Shader( void ) : program_( 0 ), ready_( false )
{}






/** Dtor.
 *  Deletes the shader from the GPU's memory.
 */
Shader::~Shader( void )
{
    if( program_ == 0 )
    {
        return;
    }

    //Get shader qty.
    GLint shader_qty;
    glGetProgramiv( program_, GL_ATTACHED_SHADERS, &shader_qty );

    //Get shader names
    GLuint* shader_names = new GLuint[shader_qty];
    glGetAttachedShaders( program_, shader_qty, NULL, shader_names );

    // Do not delete these explicitly.
    code_.vertex    = NULL;
    code_.tcs       = NULL;
    code_.tev       = NULL;
    code_.geometry  = NULL;
    code_.fragment  = NULL;
    code_.compute   = NULL;

    //Delete shaders from GPU memory.
    for( int i = 0; i < shader_qty; i++ )
    {
        glDeleteShader( shader_names[i] );
    }

    delete[] shader_names;
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
            code_.compute   = code->code;
            ids_.compute    = code->id;
            return;
    }
}




/**    Performs final compilation of the shader code on the GPU.  This must be
 *   done by the user, since it is unknown what shaders will be loaded.
 */
bool Shader::compile( void ) throw( GLSL_Program_Exception )
{
    if( !(code_.vertex || code_.fragment) )
    {
        printf( "Missing shaders." );
        return ERROR;
    }

    compile_shader( code_.vertex,   VERTEX_SHADER,      &shaders_.vertex );
    compile_shader( code_.tcs,      TCS_SHADER,         &shaders_.tcs );
    compile_shader( code_.tev,      TEV_SHADER,         &shaders_.tev );
    compile_shader( code_.geometry, GEOMETRY_SHADER,    &shaders_.geometry );
    compile_shader( code_.fragment, FRAGMENT_SHADER,    &shaders_.fragment );

    link();
    if( program_ == 0 )
    {
        throw GLSL_Program_Exception( "Unable to create shader program.\n" );
    }


    if( current_program_ == 0 )
    {
        ready_ = true;
        use_program();
    }

    return !ERROR;
}




void Shader::compile_shader(
        GLchar*   source,
        Shaders type,
        GLuint* handle )
throw( GLSL_Program_Exception )
{
    if( source == NULL )
    {
        return;
    }

    *handle = glCreateShader( type );
    glShaderSource( *handle, 1, &source, NULL );
    glCompileShader( *handle );

    int result;
    glGetShaderiv( *handle, GL_COMPILE_STATUS, &result );
    if( result == GL_FALSE )
    {
        // Compilation failed, get log.
        int length = 0;
        string log_text;
        glGetShaderiv( *handle, GL_INFO_LOG_LENGTH, &length );
        if( length > 0 )
        {
            char* log = new char[length];
            int written = 0;
            glGetShaderInfoLog( *handle, length, &written, log );
            log_text = log;
            delete [] log;
        }

        string msg;
        msg =
            get_shader_type_string( type ) + " shader with id=" + 
            numtoa( type_id( type ) ) + " compilation failed.\n" + log_text;

        throw GLSL_Program_Exception( msg );
    }

    glAttachShader( program_, *handle );
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
void Shader::link() throw( GLSL_Program_Exception )
{
    if( ready_ )
    {
        return;
    }

    if( program_ <= 0 )
    {
        throw GLSL_Program_Exception( "Program has not been compiled." );
    }

    glLinkProgram( program_ );

    int status = 0;
    glGetProgramiv( program_, GL_LINK_STATUS, &status );
    if( status == GL_FALSE )
    {
        //Get log from GPU and throw exception.
        int length = 0;
        string log_text;

        glGetProgramiv( program_, GL_INFO_LOG_LENGTH, &length );

        if( length > 0 )
        {
            char* clog = new char[length];
            int written = 0; //Dummy var.

            glGetProgramInfoLog( program_, length, &written, clog );
            log_text = clog;
            delete[] clog;
        }

        throw GLSL_Program_Exception( "Program link failed:\n" + log_text );
    }
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







/**  Gets the id of the specified shader.
 * \param t A value from the shader types enum (Shaders).
 */
int  Shader::type_id( Shaders t )
{
    switch( t )
    {
        case VERTEX_SHADER:
            return shaders_.vertex;
        case TCS_SHADER:
            return shaders_.tcs;
        case TEV_SHADER:
            return shaders_.tev;
        case GEOMETRY_SHADER:
            return shaders_.geometry;
        case FRAGMENT_SHADER:
            return shaders_.fragment;
        case COMPUTE_SHADER:
            return shaders_.compute;
        default:
            return INT_MAX;
    }
}
