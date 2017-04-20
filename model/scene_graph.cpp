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
#include "model.h"
#include "mesh.h"
#include "skybox.h"

#include "../app/window.h"

#include<cmath>


#define DEG_TO_RAD(x) ((x * 3.14159265358979f) / 180.0f)


//#define SCENE_GRAPH_DEBUG

#ifdef SCENE_GRAPH_DEBUG
# include<iostream>
#endif

namespace Model
{

    Scene_Graph*    Scene_Graph::__instance__ = NULL;




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
     * @param args A point to the SG_Setup used to initialize the graph.  NULL
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
     * @param su pointer to a setup struct. Must not be NULL.
     */
    Scene_Graph::Scene_Graph( SG_Setup* su ) :
        skybox_( NULL ),
        model_qty_( 0 ),
        models_( NULL ),
        frame_count_( 0 ),
        degrees_per_second_( 10.0f )
    {
        assert( su != NULL );

        window_ = su->win;
        assert( window_ );

        pos_ = glm::vec4( 1 );

        view_eye_ = glm::vec3(
                su->look_at_eye_x,
                su->look_at_eye_y,
                su->look_at_eye_z );
        view_tgt_ = glm::vec3(
                su->look_at_tgt_x,
                su->look_at_tgt_y,
                su->look_at_tgt_z );
        view_up_  = glm::vec3(
                    su->look_at_up_x,
                    su->look_at_up_y,
                    su->look_at_up_z );

        view_   = glm::lookAt( view_eye_, view_tgt_, view_up_ );

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
        fprintf( stdout, "%i frames rendered.", frame_count_ );

        for( GLuint i = 0; i < model_qty_; i++ )
        {
            delete models_[i];
        }
        delete [] models_;
    }




    //   I haven't been able to figure out why, but the Doxygen tags just for
    // this function do not seem to work.

    /** Adds models to be the children of the root node of the Scene_Graph.
     * @param mdl A pointer to an array of pointers to models that will be
     * added to the graph.
     * @param qty The number of models to be added.
     */
    void Scene_Graph::add_models( Model** mdl, unsigned qty )
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
            models_[model_qty_ + i] = mdl[i];
        }
        model_qty_ += qty;

        delete [] temp;
    }







    /** Calls the draw function of the root model, which in turn calls the
     * draw functions of all it's children, etc.
     */
    void Scene_Graph::draw( void )
    {
        if( degrees_per_second_ != 0.0f )
        {
            if( frame_count_ > 0 )
            {
                high_resolution_clock::time_point now  =
                    std::chrono::high_resolution_clock::now();
                duration<double> span =
                    std::chrono::duration_cast<std::chrono::microseconds>(
                            now - previous_time_ );

                GLfloat fraction = span.count();
                GLfloat deg_to_rad = DEG_TO_RAD(1.0f);

                GLfloat angle = degrees_per_second_ * deg_to_rad * fraction;

                /*
                   GLfloat x       =   view_eye_.x,
                   z       =   view_eye_.z;
                   GLfloat theta   =   DEG_TO_RAD(2.5f),
                   cs      =   cos( theta ),
                   sn      =   sin( theta );
                   view_eye_.x = (x * cs) - (z * sn);
                   view_eye_.z = (x * sn) + (z * sn);
                   */
                view_ = glm::rotate( view_, angle, glm::vec3(0, 1, 0) );
                previous_time_ = now;
            }
            else
            {
                previous_time_ = high_resolution_clock::now();
            }
        }

        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        for( GLuint i = 0; i < model_qty_; i++ )
        {
            models_[i]->render( view_, frustum_ );
        }

        if( skybox_ )
        {
            skybox_->render( view_, frustum_ );
        }

        window_->swap();

        frame_count_++;
    }






    void Scene_Graph::add_skybox(
            const string& l,
            const string& r,
            const string& u,
            const string& d,
            const string& b,
            const string& f )
    {
        /*
           fprintf( stderr,
           "Skybox set with:\n"
           "  left\t=\"%s\"\n  right\t=\"%s\"\n  top\t=\"%s\"\n"
           "  bottom\t=\"%s\"\n  back\t=\"%s\"\n  front\t=\"%s\"\n\n",
           l.c_str(), r.c_str(), u.c_str(),
           d.c_str(), b.c_str(), f.c_str()
           );
           */
        skybox_ = new Skybox( l, r, u, d, b, f );
    }




    void Scene_Graph::set_wireframe( void )
    {
        if( !skybox_ )
        {
            return;
        }
        skybox_->set_wireframe();
    }

} //Model namespace.
