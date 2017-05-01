






#include "renderer.h"
#include "mesh.h"
#include "../shader_program.h"


#include<cassert>

namespace Model
{

    Renderer::Renderer( Mesh* m, Shader* s ) :
        mesh_(m), shader_(s), additional_uniform_qty_( 0 )
    {}




    void Renderer::add_uniform( const string& name, GLenum type, void* data )
    {
        GLchar* n = new GLchar[ name.length() + 1 ];
        strncpy( n, name.c_str(), name.length() );

        types_.push_back( type );
        names_.push_back( n );
        data_.push_back( data );
        --additional_uniform_qty_;

        n = NULL;

        assert( types_.size() == names_.size() );
        assert( names_.size() == data_.size() );
        assert( names_.size() == additional_uniform_qty_ );

    }



    void Renderer::render(
            const glm::mat4& m,
            const glm::mat4& v,
            const glm::mat4& p,
            const glm::vec3& c )
    {
        shader_->use_program();

        shader_->set_uniform( "model", m );
        shader_->set_uniform( "view", v );
        shader_->set_uniform( "proj", p );
        shader_->set_uniform( "cam_pos", c );

        for( GLuint i = 0; i < additional_uniform_qty_; i++ )
        {
            switch( types_[i] )
            {
                default:
                    break;
                case GL_FLOAT:
                    shader_->set_uniform( names_[i], *(GLfloat*) data_[i] );
                    break;
                case GL_FLOAT_VEC2:
                    shader_->set_uniform( names_[i], *(glm::vec2*) data_[i] );
                    break;
                case GL_FLOAT_VEC3:
                    shader_->set_uniform( names_[i], *(glm::vec3*) data_[i] );
                    break;
                case GL_FLOAT_VEC4:
                    shader_->set_uniform( names_[i], *(glm::vec4*) data_[i] );
                    break;
                case GL_FLOAT_MAT4:
                    shader_->set_uniform( names_[i], *(glm::mat4*) data_[i] );
                    break;
                case GL_INT:
                    shader_->set_uniform( names_[i], *(GLint*) data_[i] );
                    break;
                case GL_UNSIGNED_INT:
                    shader_->set_uniform( names_[i], *(GLuint*) data_[i] );
                    break;
                case GL_BOOL:
                    shader_->set_uniform( names_[i], *(GLboolean*) data_[i];
            }
        }

        mesh_->render();
    }

}  //Model namespace.
