/**
 *
 * \file tracking_list.h
 * \author Thomas R. Carrel
 *
 *
 */


#ifndef  __TRACKING_LIST_H__
# define __TRACKING_LIST_H__

#include<unordered_map>
using std::unordered_map;
#include<vector>
using std::vector;
#include<string>
using std::string;


/** A place to store and retrieve all previously loaded meshes, to
 * allow for instanced rendering.
 */
template<typename T> class Tracking_List
{
    public:
        ~Tracking_List( void ); ///< Dtor.

        T* get( const string& );
        void add( T* );
    private:
        /** Maps the names to the pointer. */
        static unordered_map<string, T*>    data_; 
        /** Faster than itterating through a map */
        static vector<string>               names_;
};

template<typename T> unordered_map<string, T*>  Tracking_List<T>::data_;
template<typename T> vector<string>             Tracking_List<T>::names_;

template<typename T> Tracking_List<T>::~Tracking_List( void )
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
template<typename T> T* Tracking_List<T>::get( const string& n )
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
template<typename T> void Tracking_List<T>::add( T* m )
{
    if( get( m->name() ) )
    {
        return;
    }

    names_.push_back( m->name() );
    data_[ m->name() ] = m;
}

#endif /*__TRACKING_LIST_H__*/
