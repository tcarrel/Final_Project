/**
 *
 * \file vertex_array.h
 * \author vertex_array.cpp
 *
 * \brief Vertex_Array class declaration.
 *
 */


#include<GL/glew.h>

#include<SDL2/SDL.h>
#include<SDL2/SDL_opengl.h>

#include<GL/glu.h>

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>

#include<stdarg.h>

#include "vertex.h"

#ifndef  _VERTEX_ARRAY_H_
# define _VERTEX_ARRAY_H_

namespace Model
{

    /**
     * An array that can be grown as needed.
     */
    class Vertex_Array
    {
        public:
            Vertex_Array( void );
            Vertex_Array( int );
            ~Vertex_Array( void );

            void add( Vertex );

            void done( void );

            /**
             * @return The current size of the array.
             */
            GLuint size() { return size_; }


            void pre_size( unsigned );

            /** Element access.
             * \param i The index to be access.
             */
            Vertex& operator[]( unsigned i )
            { return *(data_ + i); }

            /**
             * Exposes the array used to store data,
             */
            void* data_addr( void )
            { return (void*) data_; }

            void clear( void );

            void scale( const GLfloat& );
            void center( void )
            { center( true, true, true ); }
            void center( const GLchar& );
            void center( const bool&, const bool&, const bool& );
            
        private:
            //private data.
            Vertex* data_; ///< Vertex data.

            GLuint size_; ///< Current number of indices used.
            GLuint max_size_; ///< Current size allocated in memory.

            //private functions.
            void grow( void );
    };
} //Model namespace.

#endif
