

#include<GL/glew.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_opengl.h>

#include<GL/glu.h>
#include<GL/freeglut.h>


#include<cassert>

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>

#include "SG_except.h"

#ifndef  _SCENE_GRAPH_H_
# define _SCENE_GRAPH_H

# define PERSPECTIVE true
# define ORTHOGRAPHIC false

namespace Model
{

    class Mesh;
    class Model;
    class SG_Setup;

    /**
     * The scene graph.  Renders the world, and acts as the camera view.
     */
    class Scene_Graph
    {
        public:
            /** Ctor.
            */
            Scene_Graph( SG_Setup* );
            ~Scene_Graph( void );

            void render( void ) { this->draw(); }
            void draw( void );

            //void update( );
            /*
            void add_models( Model*, GLuint );
            */

            void add_models( Mesh* );
        private:



            GLuint model_qty_; ///< Size of the model array.


            Mesh** models_;
            /*
            Model**     models_;     ///< The children of the root node of the
                                     ///< scene graph.
            */
            glm::vec4   pos_;        ///< The world xform.
            glm::mat4   view_;       ///< The view matrix for the world.
            glm::mat4   frustum_;    ///< The projection matrix for the world.

            glm::mat4 vp_;

            GLfloat aspect_;  ///< Screen aspect ratio.

            GLboolean   dirty_;


            /** Generic ctor is disabled.
             */
            Scene_Graph() {};
    };

} //Model namespace.



#endif
