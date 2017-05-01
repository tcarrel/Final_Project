/**
 * @file model.cpp
 * @author Thomas R. Carrel
 *
 * @brief Defines the Model class.
 */



#include "model.h"
#include "mesh.h"

#include<glm/gtx/transform.hpp>



namespace Model
{

    /**
     * Ctor.
     */
    Model::Model( void ) :
        mesh_( NULL ),
        dirty_( true ),
        translation_( glm::mat4(1.0f) ),
        children_( NULL )
    {}




    /**
     * Dtor.
     */
    Model::~Model( void )
    {
        mesh_->delete_this();
        mesh_ = NULL;
    }



    /** Updates the position of the model.
     */
    void Model::update( const glm::mat4& transform, bool d )
    {
        bool draw = dirty_ || d;

        if( draw )
        {
            //Update the local transformation matrix.
            for( 
                    auto iter = children_->begin(); 
                    iter != children_->end();
                    iter++
               )
            {
                //Walk the tree.
                (*iter)->update( transform, draw );
            }
            
            dirty_ = false;
        }
    }





/*
    void Model::first_pass(
            const glm::mat4& view,
            const glm::mat4& proj,
            const glm::
*/





    /**  Calls the mesh's draw command.
     * @param view The view matrix.
     * @param proj The projection matrix.
     * @param cam  The camera's position vector.
    */
    void Model::render(
            const glm::mat4& view,
            const glm::mat4& proj,
            const glm::vec3& cam ) throw(Render_Exception)
    {
        if( mesh_ )
        {
            // Draw the children.
            if( children_ )
            {
                for(
                        auto iter = children_->begin();
                        iter != children_->end();
                        iter++
                   )
                {
                    (*iter)->render( view, proj, cam );
                }
            }
            if( mesh_ )
            {
                mesh_->draw( translation_, view, proj, cam );
            }
            return;
        }

        throw( Render_Exception( "No mesh provided for model" ) );
    }






    /**  Adds the mesh for this model.  If a mesh is already set, it creates a
     * new Model object ands the mesh to that model and sets it as a child
     * model.
     * @param m The Mesh to be added.
     */
    void Model::add( Mesh* m )
    {
        if( !mesh_ )
        {
            mesh_ = m->get_ptr();
            return;
        }

        Model* temp = new Model;
        temp->add(m);
        add( temp );
        temp = NULL;
    }







    /**  Adds a model as a child.
     * @param m The Model to be added.
     */
    void Model::add( Model* m )
    {
        if( !children_ )
        {
            children_ = new std::forward_list<Model*>;
        }
        children_->push_front(m);
    }





    /**  Sets reflective environment mapping method.
     * @param sh A pointer to the Shader for reflection mapping.
     * @param sk A pointer to the Skybox for the scene.
     */
    void Model::set_reflect( Shader* sh, Skybox* sk )
    {
        if( children_ )
        {
            for(
                    auto iter = children_->begin();
                    iter != children_->end();
                    iter++ )
            {
                (*iter)->set_reflect( sh, sk );
            }
        }
        mesh_->set_reflect( sh, sk );
    }





    /**  Sets the refractive environment mapping method.
     * @param sh A pointer to the Shader for refraction mapping.
     * @param sk A pointer to the Skybox for the scene.
     * @param rr The ratio of the refractive indices of the interface between
     * both materials.
     */
    void Model::set_refract( Shader* sh, Skybox* sk, const GLfloat& rr )
    {
        if( children_ )
        {
            for(
                    auto iter = children_->begin();
                    iter != children_->end();
                    iter++ )
            {
                (*iter)->set_refract( sh, sk, rr );
            }
        }
        mesh_->set_refract( sh, sk, rr );
    }





    /**  Sets the fresnel-refraction environment mapping method.
     * @param sh A pointer to the Shader for fresnel-refraction mapping.
     * @param sk A pointer to the Skybox for the scene.
     * @param refr The ratio of the refractive indices of the interface between
     * both materials.
     * @param refl The reflective coefficient.
     */
    void Model::set_fresnel(
            Shader* sh,
            Skybox* sk,
            const GLfloat& refr,
            const GLfloat& refl )
    {
        if( children_ )
        {
            for(
                    auto iter = children_->begin();
                    iter != children_->end();
                    iter++ )
            {
                (*iter)->set_fresnel( sh, sk, refr, refl );
            }
        }
        mesh_->set_fresnel( sh, sk, refr, refl );
    }




    /**  Sets the position vector.
     * @param pos The position vector.
     */
    void Model::set_position( const glm::vec3& pos )
    {
        translation_ = glm::translate( pos );
    }



    /**  Rotate the model.
     *  @param rotate_by Rotates the model about any combination of three axes
     * in the order x, z, y.  If it is undesired to rotate about an axis, leave
     * that position in the vector 0.
     */
    void Model::rotate( const glm::vec3& rotate_by )
    {
        if( rotate_by.x != 0 )
        {
            translation_ =
                glm::rotate( translation_, glm::radians( rotate_by.x ), glm::vec3( 1, 0, 0 ) );
        }
        if( rotate_by.z != 0 )
        {
            translation_ =
                glm::rotate( translation_, glm::radians( rotate_by.z ), glm::vec3( 0, 0, 1 ) );
        }
        if( rotate_by.y != 0 )
        {
            translation_ =
                glm::rotate( translation_, glm::radians( rotate_by.y ), glm::vec3( 0, 1, 0 ) );
        }
    }
} //Model namespace.


