


#include "scene_graph.h"
#include "model.h"
#include "mesh.h"

namespace Model
{

    /** Ctor.
     * \param su pointer to a setup struct. Must not be NULL.
     */
    Scene_Graph::Scene_Graph( SG_Setup* su ) : model_qty_( 0 ), models_( new Mesh*[1] )
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
            assert( su->w != NULL );

            frustum_ = glm::perspective(
                    su->pers_angle,
                    su->w->aspect(),
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
            models_[i]->draw( NULL );
        }
    }














    ///////////////////////////////////////////////////////////
    //  SG_Setup definitions.
    ///////////////////////////////////////////////////////////









    SG_Setup::SG_Setup( void ) :
        model_x( 0.0f ),
        model_y( 0.0f ),
        model_z( 0.0f ),
        look_at_eye_y( 0.0f ),
        look_at_eye_z( 5.0f ),
        look_at_tgt_x( 0.0f ),
        look_at_tgt_y( 0.0f ),
        look_at_tgt_z( 0.0f ),
        look_at_up_x( 0.0f ),
        look_at_up_y( 1.0f ),
        look_at_up_z( 0.0f ),
        pers_angle( 35.0f ),
        ortho_left( -1.0f ),
        ortho_right( 1.0f ),
        ortho_bottom( -1.0f ),
        ortho_top ( 1.0f ),
        near( 0.0f ),
        far( 1.0f ),
        w( NULL )
    {}








    /**  Helper function for the scene graph setup struct.
     * Sets the position.
     * \param S A pointer to the setup struct.
     * \param x The x-coordinate.
     * \param y The y-coordinate.
     * \param z The z-coordinate.
     */
    void SG_Setup::position( GLfloat x, GLfloat y, GLfloat z )
    {
        this->model_x = x;
        this->model_y = y;
        this->model_z = z;
    }




    /**  Helper function for the scene graph setup struct.
     * Sets the eye position.
     * \param S A pointer to the setup struct.
     * \param x The x-coordinate.
     * \param y The y-coordinate.
     * \param z The z-coordinate.
     */
    void SG_Setup::eye_position( GLfloat x, GLfloat y, GLfloat z )
    {
        this->look_at_eye_x = x;
        this->look_at_eye_y = y;
        this->look_at_eye_z = z;
    }




    /**  Helper function for the scene graph setup struct.
     * Sets the coordinate that the camera is looking at.
     * \param S A pointer to the setup struct.
     * \param x The x-coordinate.
     * \param y The y-coordinate.
     * \param z The z-coordinate.
     */
    void SG_Setup::target( GLfloat x, GLfloat y, GLfloat z )
    {
        this->look_at_tgt_x = x;
        this->look_at_tgt_y = y;
        this->look_at_tgt_z = z;
    }  




    /**  Helper function for the scene graph setup struct.
     * Sets the up direction for the view.  The struct defaults to
     * (0, 1, 0), so calling this is not really necessary unless a
     * a different axis is desired for the up-direction or if
     * loading from a saved state where the up may be different.
     * \param S A pointer to the setup struct.
     * \param x The x-coordinate.
     * \param y The y-coordinate.
     * \param z The z-coordinate.
     */
    void SG_Setup::up_dir(
            GLfloat x = 0,
            GLfloat y = 1,
            GLfloat z = 0
            )
    {
        this->look_at_up_x = x;
        this->look_at_up_y = y;
        this->look_at_up_z = z;
    }  



    /**  Helper function for the scene graph setup struct.
     * This sets the scene graph up for the perspective projection.
     * If orthographic is already set, this will overwrite those settings.
     * \param S A pointer to the setup struct.
     * \param fov The Field Of Veiw angle.
     * \param p1 The distance to the near plane or far plane, the function
     * sets the smaller of p1 or p2 as the near plane.
     * \param p1 The distance to the near plane or far plane, the function
     * sets the greater of p1 or p2 as the far plane..
     */
    void SG_Setup::perspective(
            GLfloat fov,
            GLfloat p1,
            GLfloat p2 )
    {
        assert( p1 != p2 );

        this->is_perspective    =   PERSPECTIVE;
        this->pers_angle        =   fov;
        this->near              =   (p1 < p2) ? p1 : p2;
        this->far               =   (p1 < p2) ? p2 : p1;
    }





    /**  Helper function for the scene graph setup struct.
     * This sets the scene graph up for the orthographic projection.
     * If perspective is already set, this will overwrite those settings.
     * \param S A pointer to the setup struct.
     * \param l The distance to the left plane from the center of the view.
     * \param r The distance to the right plane from the center of the view.
     * \param b The distance to the bottom plane from the center of the view.
     * \param t The distance to the top plane from the center of the view.
     * \param n The distance to the near plane from the center of the view.
     * \param f The distance to the far plane from the center of the view.
     */
    void SG_Setup::orthographic(
            GLfloat l,
            GLfloat r,
            GLfloat b,
            GLfloat t,
            GLfloat n,
            GLfloat f )
    {
        assert( l != r );
        assert( b != t );
        assert( f != n );

        this->is_perspective    =   ORTHOGRAPHIC;
        this->ortho_left        =   l;
        this->ortho_right       =   r;
        this->ortho_bottom      =   b;
        this->ortho_top         =   t;
        this->near              =   n;
        this->far               =   f;
    }





    /**  Helper function for the scene graph setup struct.
     * This provides the pointer to the window.
     * \param S A pointer to the setup struct.
     * \param w The pointer to the window.
     */
    void SG_Setup::window( App::Window* w )
    {
        this->w = w;
    }

} //Model namespace.
