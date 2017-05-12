/**
 *
 * @file instanced.h
 * @author Thomas R. Carrel
 *
 *
 *   This will probably only be used in this current form for the upcoming demo
 * of this project.  An much better version will be necessary continuing on.
 *
 */



#include<GL/glew.h>

#include<SDL2/SDL.h>
#include<SDL2/SDL_opengl.h>

#include<GL/glu.h>

#include<cassert>

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>

#ifndef  _INSTANCED_RENDERER_H_
# define _INSTANCED_RENDERER_H_

#include<string>
using std::string;

#include "../shader_program.h"
#include "obj_loader/obj.h"

class Shader;

namespace Model
{
    namespace OBJ
    {
        class OBJ_File;
    }

    class Mesh;

    /** A proper version should probably inherit from either the Model or Mesh
     * class.
     */
    class Instanced
    {
        public:
            Instanced(
                    GLuint,
                    GLfloat,
                    GLfloat,
                    GLfloat,
                    const string&,
                    OBJ::OBJ_File*,
                    bool);
            ~Instanced( void );

            void render( const glm::mat4&, const glm::mat4& );

        private:

            GLuint      qty_;
            glm::mat4*  model_mats_;
            glm::mat4*  trans_mats_;
            
            GLfloat     radius_;
            GLfloat     offset_;
            GLfloat     max_scale_;

            Mesh*       mesh_;
            Shader*     shader_;

            GLuint      buffer_;

            static bool first_draw_;
    };

} //Model namespace.


#endif /* _INSTANCED_RENDERER_H_ */
