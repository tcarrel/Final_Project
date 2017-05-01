

#include<GL/glew.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_opengl.h>

#include<GL/gl.h>

#include<glm/glm.hpp>


#ifndef  _RENDERER_H_
# define _RENDERER_H_

#include<string>
using std::string;
#include<cstdio>
#include<vector>
using std::vector;

#include "mesh.h"
#include "../shader_program.h"

class Shader;

namespace Model
{
    class Mesh;

    class Renderer
    {
        public:
            Renderer( Mesh*, Shader* );

            void add_uniform( const string&, GLenum, void* );
            void render( 
                    const glm::mat4&,
                    const glm::mat4&,
                    const glm::mat4&,
                    const glm::vec3& );

        private:

            Mesh*                   mesh_;
            Shader*                 shader_;

            GLuint                  additional_uniform_qty_;
            vector<GLuint>          types_;
            vector<GLchar*>         names_;
            vector<void*>           data_;
    };


} //Model namespace.

#endif
