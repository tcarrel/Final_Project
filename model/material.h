/**
 *
 * @file material.h
 * @author Thomas R. Carrel
 *
 * @brief
 *
 */






#include<iostream>
using std::string;

#include<fstream>

#include<unordered_map>
using std::unordered_map;

#include<vector>
using std::vector;

#include<GL/glew.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_opengl.h>

#include<GL/gl.h>

#include<glm/glm.hpp>

#include "texture/__all_texture_types.h"

#ifndef  __MATERIAL_H__
# define __MATERIAL_H__

namespace Model
{
    class Material
    {
        public:
            Material( const string&, const string& );
            ~Material( void );

            //Getters
            const string& name( void )
            {
                return name_;
            }

            Texture::Texture_base* get_tex( const string& );

        private:

            bool newmtl(    const string&, std::istream& );
            bool N(         const string&, std::istream& );
            bool K(         const string&, std::istream& );
            bool m(         const string&, std::istream& );

            string*         path_;
            string*         filename_;
            string*         cur_mat_;
            string          name_;

            GLfloat         spec_exponent_;
            glm::vec3       ambient_;
            glm::vec3       diffuse_;
            glm::vec3       specular_;
            glm::vec3       emissive_;
            GLfloat         refractive_index_;
            GLfloat         dissolved_;;
            GLint           illum_;

            unordered_map<string, Texture::Texture_base*>   textures_;
            vector<string*>                                 mtl_names_;
    };
} //Model namespace.

#endif /*__MATERIAL_H__*/
