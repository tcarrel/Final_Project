/**
 * \file model.cpp
 * \author Thomas R. Carrel
 *
 * \brief Defines the Model class.
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
        children_( NULL )
    {}




    /**
     * Dtor.
     */
    Model::~Model( void )
    {
        delete mesh_;
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
     * \param vp The (v)iew (p)rojection matrix.
    */
    void Model::render( const glm::mat4& vp ) throw(Render_Exception)
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
                    (*iter)->render(vp);
                }
            }
            mesh_->draw(vp);
            return;
        }


        throw( Render_Exception( "No mesh provided for model" ) );
    }






    /**  Adds the mesh for this model.  If a mesh is already set, it creates a
     * new Model object ands the mesh to that model and sets it as a child
     * model.
     * \param m The Mesh to be added.
     */
    void Model::add( Mesh* m )
    {
        if( !mesh_ )
        {
            mesh_ = m;
            return;
        }

        Model* temp = new Model;
        temp->add(m);
        add( temp );
        temp = NULL;
    }







    /**  Adds a model as a child.
     * \param m The Model to be added.
     */
    void Model::add( Model* m )
    {
        if( !children_ )
        {
            children_ = new std::forward_list<Model*>;
        }
        children_->push_front(m);
    }

} //Model namespace.


