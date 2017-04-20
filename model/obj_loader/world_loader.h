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

#include "obj.h"


class Shader;

namespace App
{
    class Window;
}

namespace Model
{    
    class Mesh;
    class SG_Setup;
    class Scene_Graph;

    namespace OBJ
    {
        class World_Loader
        {
            public:
                World_Loader( App::Window* );
                ~World_Loader( void );

                bool operator()(
                        const std::string&,
                        const std::string&,
                        Scene_Graph*&,
                        bool );

                void get_errors( std::string*, unsigned* );

            private:

                void    add_error_msg(      unsigned,   const   std::string& );
                std::string* error_num_to_msg(   unsigned,   const   std::string& );

                void    scene_graph_setup( void );

                void    load_object( const std::string&, bool );
                void    load_shader( void );
                void    load_skybox( void );

                inline void print_option( const char& c )
                { fprintf( stderr, "Option: %c\n", c ); }

                OBJ_File                            obj_ld_;
                static Scene_Graph*                 sg_;

                App::Window*                        window_;
                Shader*                             cur_shader_;

                //Error handling.
                static std::vector<std::string*>*   error_msgs_;
                std::ifstream*                      file_;
        };

    } // OBJ namespace.
} // Model namespace.


#endif
