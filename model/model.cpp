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
    Model::Model( void ) : dirty_( true )
    {
    }




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
                    auto iter = children_.begin(); 
                    iter != children_.end();
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
    */
    bool Model::render( void )
    {
        if( mesh_ )
        {
//            mesh_->draw( NULL );
            // Draw the children.
            for(
                    auto iter = children_.begin();
                    iter != children_.end();
                    iter++
               )
            {
                (*iter)->render();
            }
            return !ERROR;
        }

        fprintf(
                stderr,
                "Render Error:\tNo shader set.\n"
               );

        return ERROR;
    }




    /**  Set the shader for this model.
    */
    void Model::set_program( Shader* p )
    {
        program_ = p;
    }

} //Model namespace.
