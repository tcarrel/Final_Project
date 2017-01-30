//
//  Thomas Russel Carrel
//
//  shader_program.cpp
//

#include"shader_program.h"


Shader::Shader( void )
{}

Shader::~Shader( void )
{
    glDeleteProgram( program_ );
}


/*
// Wrapers to load shaders into their appropriate variables;
bool Shader::load_vertex_shader( string filename )
{
    if( !src )
        src = new Files;

    return load_source( filename + ".vert.glsl", src->vertex_, "Vertex" );
}
bool Shader::load_fragment_shader( string filename )
{
    if( !src )
        src = new Files;

    return load_source( filename + ".frag.glsl", src->fragment_, "Fragment" );;
}

// Private load function.
bool Shader::load_source( string filename, GLchar* mem, string type )
{
    if( mem )
    {
        printf( "%s shader, already loaded.'n", type.c_str() );
        return ERROR;
    }
    ifstream file( filename.c_str() );

    if( !file.good() )
    {
        printf( "Could not open file <%s>.\n", filename.c_str() );
        return ERROR;
    }

    //Copy entire contents of file into a string;
    string* S =
        new string( 
                std::istreambuf_iterator<char>(file),
                std::istreambuf_iterator<char>() );

    //Copy into c-string.


    for( unsigned i = 0; i < S->length(); i++ )
    {
        mem[i] = (*S)[i];
    }


#ifdef DEBUG
    //Print entire shader source for debug
    std::cerr <<
        "Successfully loaded " <<
        type <<
        " Shader source file <" <<
        filename <<
        ">:\n\n" <<
        mem <<
        std::endl;
#endif

    //Clean up.
    file.close();
    delete S;
    S = NULL;

    return !ERROR;
}
*/


bool Shader::compile( const char* v, const char* f )
{
    /*
    if( !src )
    {
        printf( "<Shader::compile> No source files have been loaded.\n" );
        return ERROR;
    }

    if( !src->vertex_ )
    {
        printf( "<Shader::compile> No Vertex shader loaded.\n" );
        return ERROR;
    }

    if( !src->fragment_ )
    {
        printf( "<Shader::compile> No Fragment shader loaded.\n" );
        return ERROR;
    }

    if( !shd )
        shd = new Shaders();
    else
    {
        printf( "Cannot create more than one Shader " 
                "program per Shader object.\n" );
        return ERROR;
    }
    */

    /*const*/ GLchar** source = new GLchar*;
    //*source = new GLchar( *src->vertex_ );

    shd->vertex_   = glCreateShader( GL_VERTEX_SHADER );
    glShaderSource( shd->vertex_, 1, source, NULL );
    glCompileShader( shd->vertex_ );

    shd->fragment_ = glCreateShader( GL_FRAGMENT_SHADER );
    glShaderSource( shd->fragment_, 1, src->fragment_, NULL );
    glCompileShader( shd->fragment_ );

    if( link() )
    {
        printf( "<Shader::compile (from link())> Error occurred when" );
        printf( "linking.\n" );
        return ERROR;
    }

    // Clean up
    if( shd )
    {
        glDeleteShader( shd->vertex_ );
        glDeleteShader( shd->fragment_);
        delete shd;
        shd = NULL;
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
    glAttachShader( program_, shd->vertex_ );
    glAttachShader( program_, shd->fragment_ );

    glLinkProgram( program_ );

    return !ERROR;
}
