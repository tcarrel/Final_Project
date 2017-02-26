



#include<cassert>

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>

#include "SG_except.h"

#include "../app/window.h"


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

            GLfloat aspect_;  ///< Screen aspect ratio.

            bool model_ready_;
            bool view_ready_;
            bool proj_ready_;



            /** Generic ctor is disabled.
             */
            Scene_Graph() {};
    };










    /** Class to be filled in and submitted to Ctor of the scene graph for
     * it's initial setup.  This can be dynamically allocated and deleted
     * after setup to eliminate the struct's memory footprint.
     */
    class SG_Setup{
        public:
            SG_Setup( void );


            void position(      GLfloat,    GLfloat,    GLfloat );
            void eye_position(  GLfloat,    GLfloat,    GLfloat );
            void target(        GLfloat,    GLfloat,    GLfloat );
            void up_dir(        GLfloat,    GLfloat,    GLfloat );
            void perspective(   GLfloat,    GLfloat,    GLfloat );
            void orthographic(
                    GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat );
            void window(        App::Window* );

            /** Dtor
            */
            ~SG_Setup( void )
            { w = NULL; } // DO NOT delete this here.


            friend class Scene_Graph;
        private:

            GLfloat     model_x;  ///< World x-position.
            GLfloat     model_y;  ///< World y-position.
            GLfloat     model_z;  ///< World z-position.

            GLfloat     look_at_eye_x;    ///< Eye x-position.
            GLfloat     look_at_eye_y;    ///< Eye y-position.
            GLfloat     look_at_eye_z;    ///< Eye z-position.

            GLfloat     look_at_tgt_x;    ///< Looking at x.
            GLfloat     look_at_tgt_y;    ///< Looking at y.
            GLfloat     look_at_tgt_z;    ///< Looking at z/

            GLfloat     look_at_up_x;     ///< "Up vector" x.
            GLfloat     look_at_up_y;     ///< "Up vector" y.
            GLfloat     look_at_up_z;     ///< "Up vector" z.

            /** Whether to use perspective or othographic projection.
            */
            GLboolean   is_perspective; 

            /** FOV angle, in degrees. Must be strictly between zero and
             * 180 degrees.  When passed in.
             */
            GLfloat     pers_angle;

            GLfloat     ortho_left;   ///< Orthographic, left plane position.
            GLfloat     ortho_right;  ///< Orthographic, right plane position.
            GLfloat     ortho_bottom; ///< Orthographic, bottom plane position.
            GLfloat     ortho_top;    ///< Orthographic, top plane position.

            GLfloat     near; ///< Perspective, near plane.
            GLfloat     far; ///< Perspective, far plane.

            /**  Pointer to the window object.  Used to get the
             *  screen aspect ratio.  Must not be NULL when passed in
             *  if perspective projection is selected.
             */
            App::Window* w; 
    };





} //Model namespace.



#endif
