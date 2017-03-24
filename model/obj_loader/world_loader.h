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

#include "obj.h"

#ifndef  _LIST_LOADER_H_
# define _LIST_LOADER_H_

#include<glm/glm.hpp>


#include<fstream>
#include<string>
#include<vector>

class Shader;

namespace Model
{    
    class Mesh;
    class Scene_Graph;

    namespace OBJ
    {
        class World_Loader
        {
            public:
                World_Loader( Scene_Graph* );
                ~World_Loader( void );

                bool operator()(
                        const std::string&,
                        const std::string&,
                        Shader*,
                        bool );


                void get_errors( std::string*, unsigned* );
            private:

                void    add_error_msg(    unsigned, const std::string& );
                string* error_num_to_msg( unsigned, const std::string& );

                OBJ_File                        obj_ld_;
                static Scene_Graph*             sg_;

                //Error handling.
                static std::vector<std::string*>*   error_msgs_;
                std::ifstream*                      file_;
        };

    } // OBJ namespace.
} // Model namespace.


#endif
