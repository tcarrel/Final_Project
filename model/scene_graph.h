/**
 *
 * \file scene_graph.h
 * \author Thomas R. Carrel
 *
 * \brief The Scene_Graph "locates" the world in space.  In a way, it serves as
 * the camera or the main view of the world.  In more mathematical terms, it
 * creates the basis for the space, i.e. it creates the axes and the origin in
 * the world.  As a result, no seperate "camera" object is necessary as
 * transforming the basis moves the entire world about the camera as necessary.
 */

#include<GL/glew.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_opengl.h>

#include<GL/glu.h>
#include<GL/freeglut.h>


#include<cassert>

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>

#include "SG_except.h"
#include "../constants.h"

#ifndef  _SCENE_GRAPH_H_
# define _SCENE_GRAPH_H

namespace Model
{

    class Mesh;
    class Model;
    class SG_Setup;
    class Scene_Graph_Exception;

    /**
     * The scene graph.  Renders the world, and acts as the camera view.
     */
    class Scene_Graph
    {
        public:

            static Scene_Graph* instance( void )
                throw( Scene_Graph_Exception );
            static Scene_Graph* ctor( SG_Setup* )
                throw( Scene_Graph_Exception );

            ~Scene_Graph( void );

            /**  Just calls the draw function.  This does nothing other than
             * provide a different name for the draw function.
             */
            inline void render( void ) { this->draw(); }
            void draw( void );

            //void update( );
            /*
            void add_models( Model*, GLuint );
            */

            void add_models( Mesh* );
        private:


            /** Ctor. 
            */
            Scene_Graph( SG_Setup* );
            static Scene_Graph*
                __instance__; ///<  Scene_Graph is a singleton, but using it as
                              ///< a global variable should be avoided.

            GLuint      model_qty_; ///< Size of the model array.


            Mesh**      models_;
            /*
            Model**     models_;     ///< The children of the root node of the
                                     ///< scene graph.
            */
            glm::vec4   pos_;        ///< The world xform.
            glm::mat4   view_;       ///< The view matrix for the world.
            glm::mat4   frustum_;    ///< The projection matrix for the world.

            glm::mat4   vp_;

            GLfloat     aspect_;  ///< Screen aspect ratio.

            GLboolean   dirty_;


            /** Generic ctor is disabled.
             */
            Scene_Graph() {};
    };

} //Model namespace.



#endif
