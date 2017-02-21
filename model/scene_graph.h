



#include<cassert>

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>

#include "SG_except.h"
#include "model.h"

#include "../app/window.h"


#ifndef  _SCENE_GRAPH_H_
# define _SCENE_GRAPH_H

# define PERSPECTIVE true
# define ORTHOGRAPHIC false

namespace Model
{

    class Model;

    /** Struct to be filled in and submitted to Ctor of the scene graph for
     * it's initial setup.  This can be dynamically allocated and deleted
     * after setup to eliminate the struct's memory footprint.
     */
    struct SG_Setup{

        float model_x   =   0.0f;  ///< World x-position.
        float model_y   =   0.0f;  ///< World y-position.
        float model_z   =   0.0f;  ///< World z-position.

        float look_at_eye_x =   0.0f;    ///< Eye x-position.
        float look_at_eye_y =   0.0f;    ///< Eye y-position.
        float look_at_eye_z =   5.0f;    ///< Eye z-position.
        float look_at_tgt_x =   0.0f;    ///< Looking at x.
        float look_at_tgt_y =   0.0f;    ///< Looking at y.
        float look_at_tgt_z =   0.0f;    ///< Looking at z/
        float look_at_up_x  =   0.0f;     ///< "Up vector" x.
        float look_at_up_y  =   1.0f;     ///< "Up vector" y.
        float look_at_up_z  =   0.0f;     ///< "Up vector" z.

        /** Whether to use perspective or othographic projection.
         */
        bool  is_perspective = PERSPECTIVE; 

        /** FOV angle, in degrees. Must be strictly between zero and
         * 180 degrees.  When passed in.
         */
        float pers_angle    =   35.0f;
        float pers_near     =    0.5f; ///< Perspective, near plane.
        float pers_far      =    0.0f; ///< Perspective, far plane.

        float ortho_left;   ///< Orthographic, left plane position.
        float ortho_right;  ///< Orthographic, right plane position.
        float ortho_bottom; ///< Orthographic, bottom plane position.
        float ortho_top;    ///< Orthographic, top plane position.
        float ortho_near;   ///< Orthographic, near plane position.
        float ortho_far;    ///< Orthographic, far plane position.

        /**  Pointer to the window object.  Used to get the
         *  screen aspect ratio.  Must not be NULL when passed in
         *  if perspective projection is selected.
         */
        App::Window* window = NULL; 

        /**  A pointer to the model to be used as the root of the scene graph.
         * Must not be NULL when passed in.
         */
        Model* root_model = NULL;

        /** Dtor
         */
        ~SG_Setup( void )
        {
            window      = NULL;   ///< We do not want to free this here.
            root_model  = NULL;   ///< We do not want to free this here.
        }
    };

    /**
     * The scene graph.  For render the "world."
     */
    class Scene_Graph_Root
    {
        public:
            /** Ctor.
            */
            Scene_Graph_Root( SG_Setup* );

            void draw( void );
            //void update( void );
        private:

            Model* root_;          ///< The root of the scene graph.
            glm::vec4 pos_;        ///< The world xform.
            glm::mat4 view_;       ///< The view matrix for the world.
            glm::mat4 frustum_;    ///< The projection matrix for the world.

            float aspect_;  ///< Screen aspect ratio.

            bool model_ready_;
            bool view_ready_;
            bool proj_ready_;
    };

} //Model namespace.

#endif
