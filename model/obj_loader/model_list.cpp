/**
 *
 * \file model_list.cpp
 * \author Thomas R. Carrel
 *
 *
 */


#include "model_list.h"
#include "../mesh.h"


namespace Model
{
    namespace OBJ
    {
        
        unordered_map<string, Mesh*>    Model_list::data_;
        vector<string>                  Model_list::names_;





        Model_list::~Model_list( void )
        {
            if( names_.size() > 0 )
            {
                for( unsigned i = 0; i < names_.size(); i++ )
                {
                    data_[names_[i]] = NULL;
                }
                names_.clear();
                data_.clear();
            }
        }






        /** Gets the pointer to a Mesh that has already been loaded.
         * \param n The name of the mesh.
         * \return Returns NULL if the mesh has not yet been loaded.
         */
        Mesh* Model_list::get_mesh( const string& n )
        {
            for( unsigned i = 0; i < names_.size(); i++ )
            {
                if( names_[i] == n )
                {
                    return data_[n];
                }
            }
            return NULL;
        }






        /** Adds a loaded mesh to the list.
         * \param m The Mesh to be added.
         */
        void Model_list::add_mesh( Mesh* m )
        {
            if( get_mesh( m->name() ) )
            {
                return;
            }

            names_.push_back( m->name() );
            data_[ m->name() ] = m;
        }

    } //OBJ namespace.
} //Model namespace.
