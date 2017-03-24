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

#include<glm/glm.hpp>

#include<stdio.h>

#include<forward_list>


#include "Render_except.h"
#include "../constants.h"
#include "../shader_program.h"

class Shader;

namespace Model
{

    class Mesh;
    class Render_Exception;

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

            void update( const glm::mat4&, bool ); ///< Will need heavy
                                                   ///< modification later.

            void render( const glm::mat4&  ) throw(Render_Exception);

            void add( Mesh* );
            void add( Model* );

        private:

            Mesh*                       mesh_;
            bool                        dirty_;
            /** A list of sub-models whose position is dependant on the parent
             * model's position.
             */
            std::forward_list<Model*>*  children_;
    };

} //Model namespace.
#endif
