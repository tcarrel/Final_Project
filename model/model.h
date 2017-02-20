/**
 * \file model.h
 * \author Thomas R. Carrel
 *
 * \brief Model class declaration.
 */


#ifndef  MODEL_H
# define MODEL_H



#include<GL/glew.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_opengl.h>

#include<GL/glu.h>
#include<GL/freeglut.h>

#include<glm/glm.hpp>

#include<stdio.h>

#include<forward_list>

#include "../constants.h"
#include "../shader_program.h"

class Shader;

namespace Model
{

    class Mesh;

    /**
     * The class for a single model, eventually these will be able to contain
     * multiple meshes that are to be transformed as one unit.  This may also
     * end up as a node in the scene graph.
     */
    class Model
    {
        public:
            Model( void );
            ~Model( void );

            void update( const glm::mat4&, bool );

            bool render( void );

            void set_program( Shader* );

        private:
            Mesh* mesh_;

            //

            /** The shader program used for rendering.
             */
            Shader* program_;

            bool dirty_;
            /** A list of sub-models whose position is dependant on the parent
             * model's position.
             */
            std::forward_list<Model*> children_;
    };

} //Model namespace.
#endif
