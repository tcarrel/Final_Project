/**
 *
 * \file scene_graph.cpp
 * \author scene_graph.h
 *
 * \brief This file provides the definitions for the Scene_Graph object.
 *
 */


#include "scene_graph.h"
#include "sg_setup.h"
#include "SG_except.h"
#include "model.h"
#include "mesh.h"

#include "../app/window.h"


//#define SCENE_GRAPH_DEBUG

#ifdef SCENE_GRAPH_DEBUG
# include<iostream>
#endif

namespace Model
{

    Scene_Graph* Scene_Graph::__instance__ = NULL;




    /**  Returns the Scene_Graph object.  Throws an exception if one has not
     * already been created.
     */
    Scene_Graph* Scene_Graph::instance( void ) throw( Scene_Graph_Exception )
    {
        if( !__instance__ )
        {
            throw(
                    Scene_Graph_Exception(
                        "Scene_Graph::instance was called before the "
                        "a Scene_Graph object was instantiated." )
                 );
        }

        return __instance__;
    }


    /**  Instantiates and returns the Scene_Graph object if it has not already
     * been created or simply returns it if it has been created.
     * \param args A point to the SG_Setup used to initialize the graph.  NULL
     * can be passed in if an already created Scene_Graph is known to exist,
     * however, an exception will be thrown if NULL is passed in and no
     * Scene_Graph has yet to be created.
     */
    Scene_Graph* Scene_Graph::ctor( SG_Setup* args )
        throw( Scene_Graph_Exception )
        {
            if( !args )
            {
                if( __instance__ )
                {
                    return __instance__;
                }
                else
                {
                    throw(
                            Scene_Graph_Exception(
                                "Scene_Graph::ctor(args) called with NULL "
                                "argument before the first Scene_Graph "
                                "class was instanciated."
                                )
                         );
                }
            }

            if( !__instance__ )
            {
                __instance__ = new Scene_Graph( args );
            }

            assert( __instance__ != NULL );
            return __instance__;
        }






    /** Private Ctor.
     * \param su pointer to a setup struct. Must not be NULL.
     */
    Scene_Graph::Scene_Graph( SG_Setup* su ) :
        model_qty_( 0 ),
        models_( NULL )
    {
        assert( su != NULL );

        window_ = su->win;
        assert( window_ );

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

        vp_     =   frustum_ * view_;
        dirty_  =   true;

#ifdef SCENE_GRAPH_DEBUG
        std::cout
            << "pos_\t\t: " << glm::to_string( pos_ ) << "\n"
            << "view_\t\t: " << glm::to_string( view_ ) << "\n"
            << "frustum_\t: " << glm::to_string( frustum_ ) << "\n"
            << "vp_\t\t: " << glm::to_string( vp_ ) << std::endl;
#endif

    }; 





    /**  Dtor.
    */
    Scene_Graph::~Scene_Graph( void )
    {
        for( GLuint i = 0; i < model_qty_; i++ )
        {
            delete models_[i];
        }
        delete [] models_;
    }





    /**  Adds models to be the children of the root node of the Scene_Graph.
     * @param mdls A pointer to an array of pointers to models.
     * @param qty The number of models to be added.
     */
    void Scene_Graph::add_models( Model** mdls, unsigned qty )
    {
        Model** temp = models_;
        models_ = new Model*[model_qty_ + qty];
        for( GLuint i = 0; i < model_qty_; i++ )
        {
            models_[i] = temp[i];
            temp[i] = NULL;
        }
        for( GLuint i = 0; i < qty; i++ )
        {
            models_[model_qty_ + i] = mdls[i];
        }
        model_qty_ += qty;

        delete [] temp;
    }







    /** Calls the draw function of the root model, which in turn calls the
     * draw functions of all it's children, etc.
     */
    void Scene_Graph::draw( void )
    {

        for( GLuint i = 0; i < model_qty_; i++ )
        {
            models_[i]->render( vp_ );
        }

        window_->swap();
    }



} //Model namespace.
