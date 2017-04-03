/**
 *  \author Thomas R. Carrel
 *  \file shader_program.cpp
 *
 *  \brief Provides definitions for the Shader class.  Some of the functions in
 *  this class are based of those in "OpenGL 4 Shading Language Cookbook" by
 *  David Wolff.
 */






#include "shader_program.h"
#include "helper_functions.h"

#include<sstream>
#include<climits>


#include<glm/ext.hpp>

//helper functions

//Tracking_List<Shader> Shader::tracker_;

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
Shader* Shader::current_program_ = NULL;





/** Ctor.
 *
 */
Shader::Shader( void ) :
    program_(0),
    ready_(false),
    qty_in_use_(1)
{}






/** Dtor.
 *  Deletes the shader from the GPU's memory.  The dtor is private and can
 *  only be called by the shader object itself.  Since the object can be used
 *  an indeterminate number of times, it is necessary to prevent multi-free
 *  errors.  In order to reduce this as a possibily assigning a Shader* to a
 *  variable should be done with Shader->get_ptr() and deletion should be done
 *  with Shader->delete_this().
 */
Shader::~Shader( void )
{
    //Get shader qty.
    GLint shader_qty = 0;;
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





/**  Binds an attribute from the shader program.
 * \param location The location.
 * \param name The name of the attribute variable in the shader.
 */
void Shader::bind_attrib_location( GLuint location, const char* name )
{
    glBindAttribLocation( program_, location, name );
}



/**  Binds fragment data.
 * \param loc The location.
 * \param name The name.
 */
void Shader::bind_frag_data_location( GLuint loc, const char* name )
{
    glBindFragDataLocation( program_, loc, name );
}



/**  Sends 3-element vectors to the GPU from individual values.
 * \param name The name of the uniform.
 * \param x The first value.
 * \param y The second value.
 * \param z The third value.
 *
 */
void Shader::set_uniform( const char* name, float x, float y, float z )
{
    GLint loc = get_uniform_location(name);
    glUniform3f( loc, x, y, z );
}




/**  Sends 3-element vectors to the GPU.
 *  \param name The name of the uniform.
 *  \param v The vec3 containing the data to be sent.
 */
void Shader::set_uniform( const char* name, const glm::vec3& v )
{
    this->set_uniform( name, v.x, v.y, v.z );
}




/**  Sends 4-element vectors to the GPU.
 * \param name The name of the uniform.
 * \param v The vec4 containing the data to be sent.
 */
void Shader::set_uniform( const char* name, const glm::vec4& v )
{
    GLint loc = get_uniform_location(name);
    glUniform4f( loc, v.x, v.y, v.z, v.w );
}




/**  Sends 2-element vectors to the GPU.
 * \param name The name of the uniform.
 * \param v The vec2 containing the data to be sent.
 */
void Shader::set_uniform( const char* name, const glm::vec2& v )
{
    GLint loc = get_uniform_location(name);
    glUniform2f( loc, v.x, v.y );
}






/**  Sends a 4x4 matrix to the GPU.
 * \param name The name of the uniform.
 * \param m The mat4 to be sent.
 */
void Shader::set_uniform( const char* name, const glm::mat4& m )
{

    //    fprintf( stderr, "Set Uniformm: %s\n", glm::to_string( m ).c_str() );
    GLint loc = get_uniform_location(name);
    //    fprintf( stderr, "Uniform loc: %s, %i\n\n", name, loc );
    glUniformMatrix4fv( loc, 1, GL_FALSE, &m[0][0] );
}




/**  Sends a 3x3 matrix to the GPU.
 * \param name The name of the uniform.
 * \param m The mat3 to be sent.
 */
void Shader::set_uniform( const char* name, const glm::mat3& m )
{
    GLint loc = get_uniform_location(name);
    glUniformMatrix3fv( loc, 1, GL_FALSE, &m[0][0] );
}




/**  Sends a single floating point value to the GPU.
 * \param name The name of the uniform.
 * \param f The value to be sent.
 */
void Shader::set_uniform( const char* name, float f )
{
    GLint loc = get_uniform_location(name);
    glUniform1f( loc, f );
}





/**  Sends a single integer to the GPU.
 * \param name The name of the uniform.
 * \param i The integer to be sent.
 */
void Shader::set_uniform( const char* name, int i )
{
    GLint loc = get_uniform_location(name);
    glUniform1i( loc, i );
}





/**  Sends a single unsigned integer to the GPU.
 * \param name The name of the uniform.
 * \param u The value to be sent.
 */
void Shader::set_uniform( const char* name, GLuint u )
{
    GLint loc = get_uniform_location(name);
    glUniform1ui( loc, u );
}





/**  Sends a single boolean to the GPU.
 * \param name The name of the uniform.
 * \param b The value to be sent.
 */
void Shader::set_uniform( const char* name, bool b )
{
    GLint loc = get_uniform_location(name);
    glUniform1i( loc, b );
}






/**  Prints out all the uniform variables in the current shader program.
 * \todo Apple compatability.
 */
void Shader::print_active_uniforms( void )
{
#ifdef __APPLE__
#else
    GLint uniform_qty;

    glGetProgramInterfaceiv(
            program_,
            GL_UNIFORM,
            GL_ACTIVE_RESOURCES,
            &uniform_qty );

    GLenum properties[] = {
        GL_NAME_LENGTH,
        GL_TYPE,
        GL_LOCATION,
        GL_BLOCK_INDEX
    };

    fprintf( stdout, "Active uniforms:\n" );

    for( int i = 0; i < uniform_qty; i++ )
    {
        GLint results[4];
        glGetProgramResourceiv(
                program_,
                GL_UNIFORM,
                i,
                4,
                properties,
                4,
                NULL,
                results
                );

        if( results[3] == -1 )
        {
            GLint name_size = results[0] + 1;
            char* name = new char[name_size];
            glGetProgramResourceName(
                    program_,
                    GL_UNIFORM,
                    i,
                    name_size,
                    NULL,
                    name
                    );

            printf(
                    "%-5d %s (%s)\n",
                    results[2],
                    name,
                    get_type_string( results[1] )
                  );

            delete[] name;
        }
    }
#endif
}







/**  Prints out all the attributes in the current program.
*/
void Shader::print_active_attribs( void )
{
#ifdef __APPLE__
#else
    GLint attrib_qty;
    glGetProgramInterfaceiv(
            program_,
            GL_PROGRAM_INPUT,
            GL_ACTIVE_RESOURCES,
            &attrib_qty
            );

    GLenum props[] =
    {
        GL_NAME_LENGTH,
        GL_TYPE,
        GL_LOCATION
    };

    printf( "Active attribs:\n" );
    for( int i = 0; i < attrib_qty; i++ )
    {
        GLint results[3];
        glGetProgramResourceiv(
                program_,
                GL_PROGRAM_INPUT,
                i,
                3,
                props,
                3,
                NULL,
                results
                );

        GLint name_size = results[0] + 1;
        char* name = new char[name_size];

        glGetProgramResourceName(
                program_,
                GL_PROGRAM_INPUT,
                i,
                name_size,
                NULL,
                name
                );
        printf(
                "%-5d %s (%s)\n",
                results[2],
                name,
                get_type_string( results[1] )
              );
    }
#endif
}





/**  Prints out all of the uniform blocks in the current shader program along
 *  with a list of each of the uniforms within each block.
 */
void Shader::print_active_uniform_blocks( void )
{
#ifdef __APPLE__
#else
    GLint block_qty = 0;

    glGetProgramInterfaceiv(
            program_,
            GL_UNIFORM_BLOCK,
            GL_ACTIVE_RESOURCES,
            &block_qty
            );
    GLenum blk_props[] =
    {
        GL_NUM_ACTIVE_VARIABLES,
        GL_NAME_LENGTH
    };
    GLenum blk_index[] =
    {
        GL_ACTIVE_VARIABLES
    };
    GLenum props[] =
    {
        GL_NAME_LENGTH,
        GL_TYPE,
        GL_BLOCK_INDEX
    };

    for( int blk = 0; blk < block_qty; blk++ )
    {
        GLint blk_info[2];
        glGetProgramResourceiv(
                program_,
                GL_UNIFORM_BLOCK,
                blk,
                2,
                blk_props,
                2,
                NULL,
                blk_info
                );
        GLint uniform_qty = blk_info[0];

        char* blk_name = new char[ blk_info[1] + 1 ];
        glGetProgramResourceName(
                program_,
                GL_UNIFORM_BLOCK,
                blk,
                blk_info[1] + 1,
                NULL,
                blk_name
                );
        printf( "Uniform block \"%s\":\n", blk_name );
        delete[] blk_name;

        GLint* uniform_indices = new GLint[uniform_qty];
        glGetProgramResourceiv(
                program_,
                GL_UNIFORM_BLOCK,
                blk,
                1,
                blk_index,
                uniform_qty,
                NULL,
                uniform_indices
                );

        for( int ui = 0; ui < uniform_qty; ui++ )
        {
            GLint u_ind = uniform_indices[ui];
            GLint results[3];
            glGetProgramResourceiv(
                    program_,
                    GL_UNIFORM,
                    u_ind,
                    3,
                    props,
                    3,
                    NULL,
                    results
                    );

            GLint name_size = results[0] + 1;
            char* name = new char[name_size];
            glGetProgramResourceName(
                    program_,
                    GL_UNIFORM,
                    u_ind,
                    name_size,
                    NULL,
                    name
                    );
            printf("\t%s (%s)\n", name, get_type_string( results[1] ) );
            delete[] name;
        }
        delete[] uniform_indices;
    }
#endif
}







/**  Add pointers to the code for the current shader program.
 *  Since shader code is stored as a constant, this can be accomplished fairly
 *  easily.
 *
 * \param code The address for the struct containing the code.
 * \param type The type of shader being compiled (vertex, fragment, etc).
 */
void Shader::add_code( SHADER_TYPE_NAME* code )
{
    if( !code )
    {
        return;
    }
#ifdef DEBUG_SHADER_PROG
    fprintf(
            stderr,
            "%s\n\n",
            *code
           );
#endif
    char type = code->name[code->name.length() - 1];

    switch( type )
    {
        case 'v': //VERTEX_SHADER:
            code_.vertex    = code->code;
            ids_.vertex     = code->id;
            return;
        case 't': //TCS_SHADER:
            code_.tcs       = code->code;
            ids_.tcs        = code->id;
            return;
        case 'e': //TEV_SHADER:
            code_.tev       = code->code;
            ids_.tev        = code->id;
            return;
        case 'g': //GEOMETRY_SHADER:
            code_.geometry  = code->code;
            ids_.geometry   = code->id;
            return;
        case 'f': //FRAGMENT_SHADER:
            code_.fragment  = code->code;
            ids_.fragment   = code->id;
            return;
        case 'c': //COMPUTE_SHADER:
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
    Shader* temp = tracker_.get( id_str() );
    if( temp )
    {
        program_ = temp->program_;
        qty_in_use_ = 1; //New instance of this object.
        uniform_locations_ = temp->uniform_locations_;
        ready_ = true;
    }

    if( ready_ )
    {
        return !ERROR;
    }

    if( !(code_.vertex && code_.fragment) )
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
        throw GLSL_Program_Exception( "Unable to create shader program." );
    }


    if( current_program_ == NULL )
    {
        ready_ = true;
        use_program();
    }

    tracker_.add( id_str(), this );

    return !ERROR;
}





/**  Compiles an individual shader.
 * \param source The actual code to be compiled.
 * \param type The type of shader to be compiled.
 * \param handle The address where the shader's handle is to be stored.
 */
void Shader::compile_shader(
        GLchar*   source,
        Shaders type,
        GLuint* handle )
throw( GLSL_Program_Exception )
{

    if( program_ <= 0 )
    {
        program_ = glCreateProgram();

        if( program_ <= 0 )
        {
            throw GLSL_Program_Exception( "Unable to create shader program." );
        }
    }

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
void Shader::use_program( void ) throw(GLSL_Program_Exception)
{
    if( program_ <= 0 || !ready_ )
    {
        throw GLSL_Program_Exception( "Shader Program has not been linked." );
    }

    if( current_program_ != this )
    {
        glUseProgram( program_ );
        current_program_ = this;
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






GLint Shader::get_uniform_location( const char* name )
{
    auto pos = uniform_locations_.find(name);

    if( pos == uniform_locations_.end() )
    {
        uniform_locations_[name] = glGetUniformLocation( program_, name );
    }

    return uniform_locations_[name];
}







/** Should be used when storing pointer to a shader, this tracks the quantity
 * in used so that they can be properly deleted (or not deleted) with
 * delete_this().
 */
Shader* Shader::get_ptr( void )
{
    ++qty_in_use_;
    return this;
}






/** Tracks the number of locations where a specific instance of this shader is
 * being used and the specific instance will delete itself if it is no longer
 * needed.
 */
void Shader::delete_this( void )
{
    if( program_ == 0 )
    {
        return;
    }

    qty_in_use_--;
    if( qty_in_use_ > 0 )
    {
        return;
    }

    fprintf( stderr, "&&^^\n" );
    delete this;
}




std::string Shader::id_str( void )
{
    return
        numtoa(ids_.vertex)   + "." +
        numtoa(ids_.tcs)      + "." +
        numtoa(ids_.tev)      + "." +
        numtoa(ids_.geometry) + "." +
        numtoa(ids_.fragment) + "." +
        numtoa(ids_.compute);
}


/*
Shader* Shader::check_existance(
        SHADER_TYPE_NAME* s0, SHADER_TYPE_NAME* s1, SHADER_TYPE_NAME* s2,
        SHADER_TYPE_NAME* s3, SHADER_TYPE_NAME* s4, SHADER_TYPE_NAME* s5
        )
{
    string id =
        numtoa( s0->id ) + "." +
        numtoa( s1->id ) + "." +
        numtoa( s2->id ) + "." +
        numtoa( s3->id ) + "." +
        numtoa( s4->id ) + "." +
        numtoa( s5->id );

    return tracker_.get( id );
}
*/





/** Returns the human-readable name of the type.
 * \param t The type.
 */
const char* get_type_string( GLenum t )
{
    switch( t )
    {
        case GL_FLOAT:              return "float";
        case GL_FLOAT_VEC2:         return "vec2";
        case GL_FLOAT_VEC3:         return "vec3";
        case GL_FLOAT_VEC4:         return "vec4";
        case GL_FLOAT_MAT2:         return "mat2";
        case GL_FLOAT_MAT2x3:       return "mat2x3";
        case GL_FLOAT_MAT2x4:       return "mat2x4";
        case GL_FLOAT_MAT3:         return "mat3";
        case GL_FLOAT_MAT3x2:       return "mat3x2";
        case GL_FLOAT_MAT3x4:       return "mat3x4";
        case GL_FLOAT_MAT4:         return "mat4";
        case GL_FLOAT_MAT4x2:       return "mat4x2";
        case GL_FLOAT_MAT4x3:       return "mat4x3";

        case GL_DOUBLE:             return "double";
        case GL_DOUBLE_VEC2:        return "dvec2";
        case GL_DOUBLE_VEC3:        return "dvec3";
        case GL_DOUBLE_VEC4:        return "dvec4";
        case GL_DOUBLE_MAT2:        return "dmat2";
        case GL_DOUBLE_MAT2x3:      return "dmat2x3";
        case GL_DOUBLE_MAT2x4:      return "dmat2x4";
        case GL_DOUBLE_MAT3:        return "dmat3";
        case GL_DOUBLE_MAT3x2:      return "dmat3x2";
        case GL_DOUBLE_MAT4:        return "dmat4";
        case GL_DOUBLE_MAT4x2:      return "dmat4x2";
        case GL_DOUBLE_MAT4x3:      return "dmat4x3";

        case GL_INT:                return "int";
        case GL_INT_VEC2:           return "ivec2";
        case GL_INT_VEC3:           return "ivec3";
        case GL_INT_VEC4:           return "ivec4";

        case GL_UNSIGNED_INT:       return "unsigned int";
        case GL_UNSIGNED_INT_VEC2:  return "uvec2";
        case GL_UNSIGNED_INT_VEC3:  return "uvec3";
        case GL_UNSIGNED_INT_VEC4:  return "uvec4";

        case GL_BOOL:               return "bool";
        case GL_BOOL_VEC2:          return "bvec2";
        case GL_BOOL_VEC3:          return "bvec3";
        case GL_BOOL_VEC4:          return "bvec4";

        case GL_SAMPLER_1D:         return "sampler1D";
        case GL_SAMPLER_2D:         return "sampler2D";
        case GL_SAMPLER_3D:         return "sampler3D";

        case GL_SAMPLER_CUBE:       return "samplerCube";

        case GL_SAMPLER_1D_SHADOW:  return "sampler1DShadow";
        case GL_SAMPLER_2D_SHADOW:  return "sampler2DShadow";

        case GL_SAMPLER_1D_ARRAY:   return "sampler1DArray";
        case GL_SAMPLER_2D_ARRAY:   return "sampler2DArray";

        case GL_SAMPLER_1D_ARRAY_SHADOW:
                                    return "sampler1DArrayShadow";
        case GL_SAMPLER_2D_ARRAY_SHADOW:
                                    return "sampler2DArrayShadow";

        case GL_SAMPLER_2D_MULTISAMPLE:
                                    return "sampler2DMS";
        case GL_SAMPLER_2D_MULTISAMPLE_ARRAY:
                                    return "sampler2DMSArray";

        case GL_SAMPLER_CUBE_SHADOW:
                                    return "samplerCubeShadow";

        case GL_SAMPLER_BUFFER:     return "samplerBuffer";

        case GL_SAMPLER_2D_RECT:    return "sampler2DRect";
        case GL_SAMPLER_2D_RECT_SHADOW:
                                    return "sampler2DRectShadow";

        case GL_INT_SAMPLER_1D:     return "isampler1D";
        case GL_INT_SAMPLER_2D:     return "isampler2D";
        case GL_INT_SAMPLER_3D:     return "isampler3D";

        case GL_INT_SAMPLER_CUBE:   return "isamplerCube";

        case GL_INT_SAMPLER_1D_ARRAY:
                                    return "isampler1DArray";
        case GL_INT_SAMPLER_2D_ARRAY:
                                    return "isampler2DArray";
        case GL_INT_SAMPLER_2D_MULTISAMPLE:
                                    return "isampler2DMS";
        case GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY:
                                    return "isampler2DMSArray";
        case GL_INT_SAMPLER_BUFFER:
                                    return "isamplerBuffer";
        case GL_INT_SAMPLER_2D_RECT:
                                    return "isampler2DRect";

        case GL_UNSIGNED_INT_SAMPLER_1D:
                                    return "usampler1D";
        case GL_UNSIGNED_INT_SAMPLER_2D:
                                    return "usampler2D";
        case GL_UNSIGNED_INT_SAMPLER_3D:
                                    return "usampler3D";
        case GL_UNSIGNED_INT_SAMPLER_CUBE:
                                    return "usamplerCube";
        case GL_UNSIGNED_INT_SAMPLER_1D_ARRAY:
                                    return "usampler1DArray";
        case GL_UNSIGNED_INT_SAMPLER_2D_ARRAY:
                                    return "usampler2DArray";
        case GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE:
                                    return "usampler2DMS";
        case GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY:
                                    return "usampler2DMSArray";
        case GL_UNSIGNED_INT_SAMPLER_BUFFER:
                                    return "usamplerBuffer";
        case GL_UNSIGNED_INT_SAMPLER_2D_RECT:
                                    return "usampler2DRect"; 

        default: 
                                    return "\033[1;31;40munknown type\033[0m";
    }
}
