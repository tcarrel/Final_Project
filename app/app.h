/**
 * \file app.h
 * \author Thomas R. Carrel
 *
 * \brief Application framework (Application class) declaration.
 */

#include<GL/glew.h>

#include<SDL2/SDL.h>
#include<SDL2/SDL_opengl.h>

#include<GL/glu.h>

#include<vector>
#include<string>

#ifndef  APPLICATION_H
# define APPLICATION_H

#include "../constants.h"
#include "../shader_program.h"


#include "../input/input_handler.h"

#include<stdio.h>

namespace Model
{
    class Mesh;
    class Scene_Graph;
    class SG_Setup;
}


namespace App
{

    class Window;

    /**  The main game object.
    */
    class Application
    {
        public:
            Application( std::vector<std::string*>& );
            ~Application(void );

            int run( void ); 

        private:

            void parse_args( void );
            void command_line_help( void );

            void start_up( void );

            Window*  window_; ///< The window object that the game will be
                              ///< displayed in.

            Shader*                 shader_;
            Input::Input_Handler*   input_;
            Model::Scene_Graph*     world_;


            Model::Mesh* mesh_;

            int                         argc_;
            std::vector<std::string*>   argv_;

            int     wireframe_;
            float*  deg_per_sec_;

            string* level_filename_;

            bool    quit_;
    };

} //App namespace.

#endif
