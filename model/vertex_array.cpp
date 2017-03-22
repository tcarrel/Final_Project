/**
 *
 * \file vertex_array.cpp
 * \author Thomas R. Carrel
 *
 * \brief Definition for the Vertex_Array class.
 *
 */


#include "vertex_array.h"

#include<glm/ext.hpp>

namespace Model
{
    /** Ctor.
     * Selects an arbitrary initial size.
     */
    Vertex_Array::Vertex_Array( void ) :
        Vertex_Array( 5000 )
    {}

    /** Ctor.
     * Allows the initial size to be set on creation.
     * \param s The initial size of the array.
     */
    Vertex_Array::Vertex_Array( int s ) :
        size_( 0 ),
        max_size_( s )
    {
        data_ = new Vertex[ max_size_ ];
    }



    /** Dtor.
     */
    Vertex_Array::~Vertex_Array( void )
    {
        clear();
    }


    /** Fill vertices in the array.  Will grow the array, if necessary.
     * \param v The vertex to be added.
     */
    void Vertex_Array::add( Vertex v )
    {
        grow();
        data_[ size_++ ] = v;
    }


    /** Function to resize the array.  Initially by 50% and then increases at
     * a constant rate after the array has reached a certain size.  Ideally,
     * this will only be necessary when the game/program is initially loading,
     * as a result the overall speed is less important than the overall memory
     * footprint.
     */
    void Vertex_Array::grow( void )
    {
        if( size_ < max_size_ )
        {
            return;
        }

        Vertex* temp = data_;

        if( max_size_ < 1024 )
        {
            max_size_ *= 1.5f;
        }
        else
        {
            max_size_ += 256;
        }

        data_ = new Vertex[ max_size_ ];

        for( unsigned i; i < size_; i++ )
        {
            data_[i] = temp[i];
        }

        delete [] temp;
    }





    /**  To be called when it is no longer necessary to add vertices to the
     * array.  Shrinks the array back down to the size that is currently
     * filled.
     */
    void Vertex_Array::done( void )
    {
        if( max_size_ == size_ )
        {
            return;
        }

        Vertex* temp = data_;
        data_ = new Vertex[size_];

        for( GLuint i = 0; i < size_; i++ )
        {
            data_[i] = temp[i];
        }
        delete [] temp;

        max_size_ = size_;
    }



    /**  Sets the size of the array.  This provides faster loading if the
     * number of needed verticies is known ahead of time.  Which, in the case
     * of this program, it is.  Any data already in the array is deleted.
     * \param s The number vertices expected to be loaded.
     */
    void Vertex_Array::pre_size( unsigned s )
    {
        max_size_ = s;

        delete data_;
        data_ = new Vertex[max_size_];
    }



    /**  Clears all of the stored vertices.
     * Should be used after the vertices have all be sent to the gpu's memory.
     */
    void Vertex_Array::clear( void )
    {
        delete [] data_;
        size_ = max_size_ = 0;
        data_ = NULL;
    }

} //Model namespace.
