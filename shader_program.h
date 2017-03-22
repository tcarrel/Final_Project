/**
 *  \author Thomas R. Carrel
 *  \file shader_program.h
 *
 *  \brief Shader class declaration.
 */

#include<GL/glew.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_opengl.h>

#include<glm/glm.hpp>

#include<cassert>
#include<limits.h>

#include<string>
#include<map>

#include "constants.h"
#include "GLSL_except.h"

#include "shaders.h"

#include "helper_functions.h"

#ifndef  __SHADER_PROGRAM_H__
# define __SHADER_PROGRAM_H__



/**  A wraper class for a shader program.
 */
class Shader
{
    public:
        Shader( void );
        ~Shader(void );
        
        bool compile( void ) throw(GLSL_Program_Exception);

        /** Returns whether or not the shader program is ready for use.
         */
        bool is_linked( void );

        /** Returns the location of the program on the GPU.
         */
        inline const GLuint& get( void ) { return program_; }
        bool operator==( Shader& );
        void print( void ); 
        void add_code( SHADER_TYPE_NAME*, int );
        void use_program( void ) throw( GLSL_Program_Exception);
        

        void bind_attrib_location( GLuint, const char* );
        void bind_frag_data_location( GLuint, const char* );

        void set_uniform( const char*, float, float, float );
        void set_uniform( const char*, const glm::vec3& );
        void set_uniform( const char*, const glm::vec4& );
        void set_uniform( const char*, const glm::vec2& );
        void set_uniform( const char*, const glm::mat4& );
        void set_uniform( const char*, const glm::mat3& );
        void set_uniform( const char*, float );
        void set_uniform( const char*, int );
        void set_uniform( const char*, GLuint );
        void set_uniform( const char*, bool );
        
        void print_active_uniforms( void );
        void print_active_attribs( void );
        void print_active_uniform_blocks( void );

    private:

        void compile_shader( GLchar*, Shaders, GLuint* )
            throw( GLSL_Program_Exception );
        void link( void ) throw( GLSL_Program_Exception ); ///< Called by
                                                           ///< compile().
        int type_id( Shaders );

        struct 
        {
            GLchar* vertex      = NULL;
            GLchar* tcs         = NULL;
            GLchar* tev         = NULL;
            GLchar* geometry    = NULL;
            GLchar* fragment    = NULL;
            GLchar* compute     = NULL;
        } code_; ///<  Pointers to the source code for the various shaders.

        struct
        {
            GLuint  vertex      = 0;
            GLuint  tcs         = 0;
            GLuint  tev         = 0;
            GLuint  geometry    = 0;
            GLuint  fragment    = 0;
            GLuint  compute     = 0;
        } ids_; ///< Store the ids of the individual shaders.  This may be used
        ///< later for some additional optimization.

        struct 
        {
            GLuint  vertex;
            GLuint  tcs;
            GLuint  tev;
            GLuint  geometry;
            GLuint  fragment;
            GLuint  compute;
        } shaders_; ///< The location of the shaders in the GPU's memory.

        GLuint      program_; ///<  The handle for the shader program after
        ///< it's been compiled.
        bool        ready_; ///<  Flag indicating the shader has been compiled,
        ///< linked, and is ready for use.

        static Shader* current_program_; ///< Used to reduce the number
        ///< glUseProgram calls.


        std::map<std::string, int> uniform_locations_;


        GLint get_uniform_location( const char* );

        //Prevent copying
        Shader( const Shader& o ) { };
        Shader& operator=( const Shader& o ) { return *this; }

};  // Shader class.

const char* get_type_string( GLenum );

#endif /* __SHADER_PROGRAM_H__ */
