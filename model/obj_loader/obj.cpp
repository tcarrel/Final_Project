/**
 *
 * \file obj.cpp
 * \author Thomas R. Carrel
 *
 */


#include "obj.h"
#include "../vertex_array.h"
#include "../vertex.h"
#include "../../colors.h"
#include "../../helper_functions.h"


namespace Model
{
    namespace OBJ
    {

        /** Generic ctor.
         */
        OBJ_File::OBJ_File( void ) : opened_( false )
        {}

        /** OBJ Loader ctor.
         * \param f The name (and, optionally, the path) of the wavefront .obj
         * file to be parsed.
         */
        OBJ_File::OBJ_File( const string& f ) 
        {
            open( f );
        }

        /** Dtor
         */
        OBJ_File::~OBJ_File( void )
        {
            if( file_.is_open() )
            {
                file_.close();
            }
            //Additional work to be done here.
        }




    } //OBJ namespace.

} //Model namespace.
