/**
 *
 * @file skybox.h
 * @author Thomas R. Carrel
 *
 */

#include<GL/glew.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_opengl.h>

#include<GL/glu.h>

#include<glm/glm.hpp>
#include<glm/gtx/transform.hpp>

#include<SOIL/SOIL.h>

#include<string>
#include<cassert>

#ifndef  _SKYBOX_MODEL_H_
# define _SKYBOX_MODEL_H_

class Shader;

namespace Model
{

    class Skybox
    {
        public:
            Skybox(
                    const std::string&, const std::string&,
                    const std::string&, const std::string&,
                    const std::string&, const std::string& );

            void render( const glm::mat4&, const glm::mat4& );

        private:
            void load_textures( std::string* );

            Shader* program_handle_;
            GLuint  texture_handle_;
            GLuint  vao_;
            GLuint  vbo_;
    };
} //Model namespace.

#endif /*_SKYBOX_MODEL_H_*/

