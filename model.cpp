/**
 * \file model.cpp
 * \author Thomas R. Carrel
 *
 */



#include "model.h"
#include "mesh.h"




/**
 * Ctor.
 */
Model::Model( void )
{
}




/**
 * Dtor.
 */
Model::~Model( void )
{
}




/**  Calls the mesh's draw command.
 */
bool Model::render( void )
{
    if( mesh_ )
    {
        mesh_->draw( NULL );
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
