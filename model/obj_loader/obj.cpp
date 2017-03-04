/**
 *
 * \file obj.cpp
 * \author Thomas R. Carrel
 *
 */


#include "obj.h"
#include "OBJ_except.h"

#include "../vertex_array.h"
#include "../vertex.h"
#include "../../colors.h"
#include "../../helper_functions.h"

#include<iostream>
using std::istream;

#include<cstdio>
#include<cstdlib>

// Local helper functions.








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



        void OBJ_File::parse( void ) throw( OBJ_Exception )
        {
           if( !is_open() )
           {
               fprintf( stderr, "Filename: %s\n", filename_->c_str() );
               fflush( stderr );
               throw(
                       OBJ_Exception( "Could not open .obj file." )
                    );
           }

           string start;

           if( !eof() )
           {
               return;
           }

           file_ >> start;

           switch( start[0] )
           {
               case '#': //comment
                   getline( file_, start );
                   file_.ignore();
                   break;
               case 'v':
                   if( start.length() == 1 )
                   {
                       vertex();
                   }
                   else
                   {
                       v( start );
                   }
                   break;
               case 'g':

                   break;
               case 'f':

                   break;
               case 'm':
               default:
                   fprintf(
                           stderr,
                           "Character <%c>.\nFile <%s>.\n",
                           start[0],
                           filename_->c_str()
                          );
                   fflush( stderr );
                   throw(
                           OBJ_Exception( "Unexpected character." )
                        );
           }
           parse();
        }






        /**  Determines what to parse for lines beginning with 'v'.
         * \param s A string containing the first 'word' of the current line.
         */
        void OBJ_File::v( string& s )
        {
            string dummy;

            switch( s[2] )
            {
                case 't': //Texture coordinate.
                    tex_coord();
                    break;
                case 'n':
                    normal();
                    break;
                case 'p':
                    getline( file_, dummy );
                    break;
                default:
                    fprintf( stderr,
                            ".obj parsing error.\n"
                            "Discarding current line.\n"
                            "Model, file <%s>, may not render correctly.\n",
                            filename_->c_str()
                           );
                    getline( file_, dummy );
                    file_.ignore();
            }

            return;
        }






        /** Parses a single vertex coordinate, discards the w-coordinate
         * since that always needs to be set to 1.
         */
        void OBJ_File::vertex( void )
        {
            float x, y, z;
            string dummy;
            file_ >> x;
            file_ >> y;
            file_ >> z;

            vertices_.push_back( glm::vec3( x, y, z ) );
            getline( file_, dummy );
            file_.ignore();
        }




        /** Parses a normal coordinate.
         */
        void OBJ_File::normal( void )
        {
        }



        /** Parses a texture coordinate.
         */
        void OBJ_File::tex_coord( void )
        {
            float s, v;
            string dummy;
            file_ >> s;
            file_ >> v;

            textures_.push_back( glm::vec2( s, v ) );
            getline( file_, dummy );
            file_.ignore();
        }



    } //OBJ namespace.

} //Model namespace.
