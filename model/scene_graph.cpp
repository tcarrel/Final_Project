


#include "scene_graph.h"
#include "sg_setup.h"
#include "model.h"
#include "mesh.h"

namespace Model
{

    /** Ctor.
     * \param su pointer to a setup struct. Must not be NULL.
     */
    Scene_Graph::Scene_Graph( SG_Setup* su ) :
        model_qty_( 0 ),
        models_( new Mesh*[1] )
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
            assert( su->pers_aspect > 0 );

            frustum_ = glm::perspective(
                    su->pers_angle,
                    su->pers_aspect,
                    su->near,
                    su->far
                    );
        }
        else
        {
            frustum_ = glm::ortho(
                    su->ortho_left,
                    su->ortho_right,
                    su->ortho_bottom,
                    su->ortho_top,
                    su->near,
                    su->far
                    );

        }

        vp_     =   view_ * frustum_;
        dirty_  =   false;
    }; 



    

    /**  Dtor.
     */
    Scene_Graph::~Scene_Graph( void )
    {
        /*
        for( int i = 0; i < model_qty_; i++ )
        {
            delete moodels_[i];
        }
        delete [] models_;
        */

        if( models_[0] )
        {
            delete models_[0];
        }
        delete [] models_;
    }






    /**  Adds models to be the children of the scene graph's root node.
     * \param m A pointer to the model.
     */
#if 0
    void Scene_Graph::add_models( Model* m, unsigned qty );
#endif
    void Scene_Graph::add_models( Mesh* m )
    {
        if( !m )
        {
            return;
        }

        models_[0] = m;
        model_qty_ = 1;

#if 0
        Models** temp = models_;
        models_ = new Models*[model_qty_ + qty];
        for( int i = 0; i < model_qty_; i++ )
        {
            models_[i] = temp[i];
            temp[i] = NULL;
        }
        for( int i = 0; i < qty; i++ )
        {
            models_[model_qty + i] = m[i];
        }
        model_qty_ += qty;

        delete [] temp;
#endif
    }







    /** Calls the draw function of the root model, which in turn calls the
     * draw functions of all it's children, etc.
     */
    void Scene_Graph::draw( void )
    {
        for( GLuint i = 0; i < model_qty_; i++ )
        {
            models_[i]->draw( NULL, dirty_ ? NULL : &vp_ );
        }
    }



} //Model namespace.
