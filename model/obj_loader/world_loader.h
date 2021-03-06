/**
 *
 *
 * \file world_loader.h
 * \author Thomas R. Carrel
 *
 */






#include<GL/glew.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_opengl.h>

#include<GL/glu.h>

#ifndef  _LIST_LOADER_H_
# define _LIST_LOADER_H_

#include<glm/glm.hpp>

#include<fstream>
#include<string>
#include<vector>

#include "World_except.h"


class Shader;

namespace App
{
    class Window;
}

namespace Model
{    
    class Mesh;
    class Model;
    class SG_Setup;
    class Scene_Graph;

    namespace OBJ
    {
        class World_Exception;
        class OBJ_File;

        class World_Loader
        {
            public:
                World_Loader( App::Window* );
                ~World_Loader( void );

                inline bool operator()(
                        const std::string& p,
                        Scene_Graph*& sg,
                        bool b )
                { return this->operator()( p, "DEFAULT.cn", sg, b ); }

                bool operator()(
                        const std::string&,
                        const std::string&,
                        Scene_Graph*&,
                        bool );

                void get_errors( std::string*, unsigned* );

            private:

                void add_error_msg(
                        unsigned,
                        const std::string& );
                std::string* error_num_to_msg(
                        unsigned,
                        const std::string& );

                void    scene_graph_setup( void );

                void    load_object( const std::string&, bool )
                    throw(World_Exception);
                void    load_shader( void );
                void    load_skybox( void );

                void    mirrored( Model* );
                void    transparent( Model* );
                void    fresnel_transparency( Model* );

                void    read_vec3( glm::vec3& );

                void    load_instanced( const std::string&, bool );

                inline void print_option( const char& c )
                { fprintf( stderr, "Option: %c ", c ); }

                OBJ_File                            obj_ld_;
                static Scene_Graph*                 sg_;

                App::Window*                        window_;
                Shader*                             cur_shader_;

                //Error handling.
                static std::vector<std::string*>*   error_msgs_;

                std::ifstream*                      file_;

                bool                                skybox_is_loaded_;
        };

    } // OBJ namespace.
} // Model namespace.


#endif
