/**
 * @file model.cpp
 * @author Thomas R. Carrel
 *
 * @brief Defines the Model class.
 */



#include "model.h"
#include "mesh.h"





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


    /**  Calls the mesh's draw command.
     * @param vp The (v)iew (p)rojection matrix.
    */
    void Model::render( const glm::mat4& view, const glm::mat4& proj ) throw(Render_Exception)
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
                    (*iter)->render( view, proj );
                }
            }
            if( mesh_ )
            {
                mesh_->draw( translation_, view, proj );
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





    /**  Sets the position vector.
     * @param x The x-coordinate.
     * @param y The y-coordinate.
     * @param z The z-coordinate.
     */
    void Model::set_position( GLfloat& x, GLfloat& y, GLfloat& z )
    {
//        pos_ = glm::translate( x, y, z );
        /*
        pos_ = glm::mat4(
                pos_[0][0], pos_[1][0], pos_[2][0], pos_[3][0],
                pos_[0][1], pos_[1][1], pos_[2][1], pos_[3][1],
                pos_[0][2], pos_[1][2], pos_[2][2], pos_[3][2],
                x         , y         , z         , 1.0f );
                */
//        pos_ = glm::translate( glm::mat4(1.0f), glm::vec3(x, y, z) );
        translation_ = glm::translate( glm::vec3( x, y, z ) );
    }

} //Model namespace.


