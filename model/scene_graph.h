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

#include<cassert>

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>

#include "SG_except.h"
#include "../constants.h"

#include<chrono>
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;

#ifndef  _SCENE_GRAPH_H_
# define _SCENE_GRAPH_H

class Shader;

namespace App
{
    class Window;
} // App namespace

namespace Model
{

    class Mesh;
    class Model;
    class SG_Setup;
    class Skybox;
    class Instanced;

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


            /**  Just calls the draw function.  This does nothing other than
             * provide a different name for the draw function.
             */
            inline void render( void ) { this->draw(); }
            void draw( void );

            //void update( );

            void add_models( Model**, GLuint );
            void add_skybox(
                    const string&,
                    const string&,
                    const string&,
                    const string&,
                    const string&,
                    const string&
                    );

            void set_wireframe( void );
            void set_dps( const GLfloat& dps )
            { degrees_per_second_ = dps; }

            inline Skybox* get_skybox_ptr( void )
            { return skybox_; }
            inline Shader* get_mirror_prog( void )
            { return mirror_; }
            inline Shader* get_refract_prog( void )
            { return transparent_; }
            inline Shader* get_fresnel_prog( void )
            { return fresnel_; }

            void set_instanced( Instanced* );

            void get_frame_rate_data( GLuint& count, GLfloat& rate )
            {
                count = frame_count_;
                rate  = avg_seconds_per_frame_;
            }

            ~Scene_Graph( void );


            int get_vertex_qty( void );

        private:
            
            friend void delete_sg( void );

            /** Ctor. 
            */
            Scene_Graph( SG_Setup* );

            /**  Scene_Graph is a singleton, but using it as a global variable
             * should be avoided.
            */
            static Scene_Graph* __instance__;

            Skybox*     skybox_;

            Shader*     mirror_;
            Shader*     fresnel_;
            Shader*     transparent_;
            
            GLuint      model_qty_; ///< Size of the model array.

            Model**     models_;  ///< The children of the root node of the
            ///< Scene_Graph.

            glm::vec4   pos_;     ///< The world xform.

            glm::vec3   view_eye_, view_tgt_, view_up_;

            glm::mat4   view_;    ///< The view matrix for the world.
            glm::mat4   frustum_; ///< The projection matrix for the world.

            glm::mat4   vp_;

            GLfloat     aspect_;  ///< Screen aspect ratio.

            GLboolean   dirty_;

            App::Window* window_;

            GLuint      frame_count_;

            high_resolution_clock::time_point previous_time_;
            GLfloat degrees_per_second_;
            GLfloat avg_seconds_per_frame_;

            Instanced*  instanced_;

            /** Generic ctor is disabled.
            */
            Scene_Graph() {};
    };

} //Model namespace.


#endif
