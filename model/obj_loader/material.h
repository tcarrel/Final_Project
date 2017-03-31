/**
 *
 * @file material.h
 * @author Thomas R. Carrel
 *
 * @brief
 *
 */






# include<iostream>
using std::string;
# include<fstream>


#include<GL/glew.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_opengl.h>

#include<GL/gl.h>

#include<glm/glm.hpp>

#include "../texture/__all_texture_types.h"


#ifndef  __MATERIAL_H__
# define __MATERIAL_H__

namespace Model
{
    namespace OBJ
    {
        class Material
        {
            public:
                Material(const std::string& n) : name_(n) {}





                //Getters
                const string& name( void ) { return name_; }
            private:

                std::string     name_;

                glm::vec3       ambient_;
                glm::vec3       diffuse_;
                glm::vec4       specular_;
                glm::vec3       emissive_;
                GLflaot         Ni_;
                Glfloat         dissolved_;;
                Glint           illum_;

//                Texture_base* 
        }
    } //OBJ namespace.
} //Model namespace.

#endif /*__MATERIAL_H__*/
