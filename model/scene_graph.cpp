


#include "scene_graph.h"
#include "model.h"

namespace Model
{

    /** Ctor.
     * \param su pointer to a setup struct. Must not be NULL.
     */
    Scene_Graph_Root::Scene_Graph_Root( SG_Setup* su ) 
    {
        assert( su != NULL );

        pos_  = glm::vec4( su->model_x, su->model_y, su->model_z, 1.0f );

        view_   = glm::lookAt(
                glm::vec3(
                    su->look_at_eye_x,
                    su->look_at_eye_y,
                    su->look_at_eye_z
                    ),
                glm::vec3(
                    su->look_at_tgt_x,
                    su->look_at_tgt_y,
                    su->look_at_tgt_z
                    ),
                glm::vec3(
                    su->look_at_up_x,
                    su->look_at_up_y,
                    su->look_at_up_z
                    )
                );

        if( su->is_perspective == PERSPECTIVE )
        {
            assert( su->pers_angle > 0.0f );
            assert( su->pers_angle < 180.0f );
            assert( su->window != NULL );

            frustum_ = glm::perspective(
                    su->pers_angle,
                    su->window->aspect(),
                    su->pers_near,
                    su->pers_far
                    );
        }
        else
        {
            frustum_ = glm::ortho(
                    su->ortho_left,
                    su->ortho_right,
                    su->ortho_bottom,
                    su->ortho_top,
                    su->ortho_near,
                    su->ortho_far
                    );

        }

        assert( su->root_model != NULL );
        root_ = su->root_model;
    }; 





    /** Calls the draw function of the root model, which in turn calls the
     * draw functions of all it's children, etc.
     */
    void Scene_Graph_Root::draw( void )
    {
    }

} //Model namespace.
