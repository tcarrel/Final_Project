/**
 *
 * @file skybox.h
 * @author Thomas R. Carrel
 *
 * @brief Provides functionality for skyboxes and environment mapping.
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

    /**  Handles skyboxes/cubemaps and environment maps.
     */
    class Skybox
    {
        public:
            Skybox(
                    const std::string&, const std::string&,
                    const std::string&, const std::string&,
                    const std::string&, const std::string& );

            void render( const glm::mat4&, const glm::mat4& );

            void set_wireframe( void );

            void get_reflect_data( GLuint*, GLenum* );

            inline GLuint get_tex_handle( void )
            { return texture_handle_; }

        private:
            void load_textures( std::string* );

            Shader* program_handle_;
            GLuint  texture_handle_;
            GLuint  vao_;
            GLuint  vbo_;

            GLuint  wf_;
    };
} //Model namespace.

#endif /*_SKYBOX_MODEL_H_*/

