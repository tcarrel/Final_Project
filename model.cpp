/**
 * \file model.cpp
 * \author Thomas R. Carrel
 *
 */



#include "model.h"



Model::Model( void )
{
}


Model::~Model( void )
{
}


bool Model::render( void )
{
    return false;
}


void Model::set_program( Shader* p )
{
    program_ = p;
}
