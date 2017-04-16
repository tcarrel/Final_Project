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

#include "../shader_program.h"


#ifndef  _SKYBOX_MODEL_H_
# define _SKYBOX_MODEL_H_

namespace Model
{

    class Skybox
    {
        public:
            Skybox(
                    const std::string&, const std::string&,
                    const std::string&, const std::string&,
                    const std::string&, const std::string& );

        private:
            void load_textures( std::string* );

            Shader* program_handle_;
            GLuint  texture_handle_;
    };
} //Model namespace.

#endif /*_SKYBOX_MODEL_H_*/

