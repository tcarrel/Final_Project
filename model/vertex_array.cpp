/**
 *
 * \file vertex_array.cpp
 * \author Thomas R. Carrel
 *
 * \brief Definition for the Vertex_Array class.
 *
 */


#include "vertex_array.h"


namespace Model
{
    /** Ctor.
     * Selects an arbitrary initial size.
     */
    Vertex_Array::Vertex_Array( void ) :
        Vertex_Array( 36 )
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
        delete [] data_;
        data_ = NULL;
    }



    /*
    void Vertex_Array::add( int n, ... )
    {
        va_list vl;
        va_start( vl, n );

        for( int i = 0; i < n; i++ )
        {
            add( va_arg( vl, Vertex ) );
        }

        va_end( vl );
    }
    */

    /** Fill vertices in the array.  Will grow the array, if necessary.
     * \param v The vertex to be added.
     */
    void Vertex_Array::add( Vertex v )
    {
        if( size_ >= max_size_ )
            grow();

        data_[ size_ ] = v;
        ++size_;
    }


    /** Function to resize the array.  Initially by 50% and then increases at
     * a constant rate after the array has reached a certain size.  Ideally,
     * this will only be necessary when the game/program is initially loading,
     * as a result the overall speed is less important than the overall memory
     * footprint.
     */
    void Vertex_Array::grow( void )
    {
        Vertex* temp = data_;

        if( max_size_ < 1024 )
        {
            max_size_ *= 1.5f;
        }
        else
        {
            max_size_ += 256;
        }

        for( unsigned i; i < size_; i++ )
        {
            data_[i] = temp[i];
        }

        delete [] temp;
    }
} //Model namespace.
