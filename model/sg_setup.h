/**
 *
 * \file sg_setup.h
 * \author Thomas R. Carrel
 *
 * \brief Declares the SG_Setup object that is used to initialize the
 * Scene_Graph.
 */

#include<cassert>

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>

#ifndef  _SG_SETUP_H_
# define _SG_SETUP_H_

#include "../constants.h"
#include "../app/window.h"


namespace Model
{


    class Scene_Graph;

    /**  Required to call the Scene_Graph ctor. Because the Scene_Graph object
     * requires a very large amount of data in order for its constructor to
     * work correctly and--for very good reason--has no setter functions for
     * many of its fields, this class provides a better way of correctly
     * constructing the Scene_Graph than calling a ctor with twenty-one
     * arguments.  It is no longer needed after the Scene_Graph is created
     * and, therefore, can be created dynamically, filled, and then deleted
     * after the creation of Scene_Graph.
     */
    class SG_Setup{
        public:
            SG_Setup( void );

            void position(      GLfloat,    GLfloat,    GLfloat );
            void eye_position(  GLfloat,    GLfloat,    GLfloat );
            void target(        GLfloat,    GLfloat,    GLfloat );
            void up_dir(        GLfloat,    GLfloat,    GLfloat );
            void perspective(   GLfloat,    GLfloat,    GLfloat,    GLfloat );

            /**  Helper function for the scene graph setup struct.
             * This sets the scene graph up for the perspective projection.
             * If orthographic is already set, this will overwrite those
             * settings.
             * \param fov The Field Of Veiw angle.
             * \param p1 The distance to the near plane or far plane, the
             * function sets the smaller of p1 or p2 as the near plane.
             * \param p2 The distance to the near plane or far plane, the
             * function sets the greater of p1 or p2 as the far plane..
             * \param w A pointer to the window.
             */
            inline void perspective(
                    GLfloat fov,
                    GLfloat p1,
                    GLfloat p2,
                    App::Window* w )
            {
                this->perspective( fov, p1, p2, w->aspect() );
            }

            void orthographic(
                    GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat );
            void window(        App::Window* );

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

            GLfloat     pers_aspect;  ///< Screen aspect ratio.

            GLfloat     ortho_left;   ///< Orthographic, left plane position.
            GLfloat     ortho_right;  ///< Orthographic, right plane position.
            GLfloat     ortho_bottom; ///< Orthographic, bottom plane position.
            GLfloat     ortho_top;    ///< Orthographic, top plane position.

            GLfloat     near; ///< Perspective, near plane.
            GLfloat     far; ///< Perspective, far plane.

            App::Window*    win;
    };


} //Model namespace.


#endif
