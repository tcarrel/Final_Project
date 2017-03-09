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
using std::endl;
#include<sstream>
using std::stringstream;


#include<cstdio>
#include<cstdlib>
#include<cctype>


#include<glm/ext.hpp>

// Local helper functions.







namespace Model
{
    namespace OBJ
    {

        /** Generic ctor.
         */
        OBJ_File::OBJ_File( void ) :
            filename_(NULL),
            obj_name_(NULL)
        {
            tracing_ = false;
            line_ = 0;
        }

        /** OBJ Loader ctor.
         * \param f The name (and, optionally, the path) of the wavefront .obj
         * file to be parsed.
         */
        OBJ_File::OBJ_File( const string& f ) :
            filename_(NULL),
            obj_name_(NULL)
        {
            tracing_ = false;
            line_ = 0;
            if( is_open() )
            {
                close();
            }
            open( f );
        }

        /** Dtor
         */
        OBJ_File::~OBJ_File( void )
        {
            reset();
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

           if( !eof() )
           {

               while( isspace( peek() ) )
               {
                   file_.ignore();
               }

               switch( peek() )
               {
                   case '#': //comment
                       comment();
                       break;
                   case 'v':
                       v();
                       break;
                   case 'g':
                       g();
                       break;
                   case 'f':
                       f();
                       break;
                   case 'm':
                       m();
                       break;
                   case 'o':
                       o();
                       break;
                   case 's':
                       s();
                       break;
                   case 'u':
                       u();
                       break;
                   case ' ':
                   case '\t':
                   case '\n':
                   case '\f':
                   case '\v':
                   case '\r':
                       file_.ignore();
                       break;
                   default:
                       /*
                          fprintf(
                          stderr,
                          "Character <%c>.\nFile <%s>.\n",
                          peek(),
                          filename_->c_str()
                          );
                          fflush( stderr );
                          throw(
                          OBJ_Exception( "Unexpected character." )
                          );
                          */
                       ;
               }
               ++line_;
               parse();
           }
        }






        /**  Determines what to parse for lines beginning with 'v'.
        */
        void OBJ_File::v( void )
        {
            string s;

            file_ >> s;

            if( s == "v" )
            {
                vertex();
                return;
            }

            if( s == "vt" )
            {
                tex_coord();
                return;
            }

            if( s == "vn" )
            {
                normal();
                return;
            }

            if( s == "vp" )
            {
                if( tracing_ )
                {
                    trace_ << "### Paramaterized ###" << endl;
                }
                comment();
            }


            fprintf( stderr,
                    ".obj parsing error.\n"
                    "Discarding current line.\n"
                    "Model, file <%s>, may not render correctly.\n",
                    filename_->c_str()
                   );
            comment();
        }


        /** Parses a 'g' line.
        */
        void OBJ_File::g()
        {
            if( tracing_ )
            {
                trace_ << "### g ###" << endl;
            }
            comment();
        }


        /** Parses an 'f' line.
        */
        void OBJ_File::f()
        {
            string v;
            file_ >> v;

            if( tracing_ )
            {
                trace_ << "$$$ Read Face: ";
            }

            for( int j = 0; j < 3; j++ )
            {
                int val[3];
                Index_Set*  index   = new Index_Set;

                faces_.push_back( index );

                file_ >> val[0];
                if( peek() != ' ' )
                {
                    file_.ignore();
                }
                else
                {
                    index->v = val[0];
                    index = NULL;
                    continue;
                }

                if( isdigit( peek() ) )
                {
                    file_ >> val[1];
                }
                else
                {
                    val[1] = 0;
                }
                file_.ignore();
                file_ >> val[2];            

                for( int i = 0; i < 3; i++ )
                {
                    if( val[i] > 0 )
                    {
                        --val[i]; // Indicies in .obj file start at 1.
                    }
                    else if( val[i] < 0 )
                    {
                        switch( i )
                        {
                            case 0:
                                val[i] += vertices_.size();
                                break;
                            case 1:
                                val[i] += textures_.size();
                                break;
                            case 2:
                                val[i] += normals_.size();
                            default:
                                ;
                        }
                    }
                    //Do nothing if ind[i] == 0.
                }

                index->v = val[0];
                index->t = val[1];
                index->n = val[2];

                if( tracing_ )
                {
                    trace_ << val[0] << "/" << val[1] << "/" << val[2] << " ";
                }

                //Index set has already been pushed onto the vector.
                index = NULL;
            }

            if( tracing_ )
            {
                trace_ << endl;
            }
        }

        /** Parses an 'm' line.
        */
        void OBJ_File::m( void )
        {
            if( tracing_ )
            {
                trace_ << "### m ###" << endl;
            }
            comment();
        }

        /** Parses an 'o' line.
        */
        void OBJ_File::o( void )
        {
            if( !obj_name_ )
            {
                obj_name_ = new string;
            }

            file_ >> *obj_name_;
            file_ >> *obj_name_;

            if( tracing_ )
            {
                trace_ << "Object Name:  " << *obj_name_ << endl;
            }
        }

        void OBJ_File::s( void )
        {
            if( tracing_ )
            {
                trace_ << "### s ###" << endl;
            }
            comment();
        }


        void OBJ_File::u( void )
        {
            if( tracing_ )
            {
                trace_ << "### u ###" << endl;
            }
            comment();
        }


        /** Parses a single vertex coordinate, discards the w-coordinate
         * since that always needs to be set to 1.
         */
        void OBJ_File::vertex( void )
        {
            float x, y, z;
            file_ >> x;
            file_ >> y;
            file_ >> z;

            glm::vec3 v( x, y, z );
            if( tracing_ )
            {
                trace_
                    << "Read vertex: ("
                    << x << ") (" << y << ") (" << z << ")\n"
                    << glm::to_string( v ) << endl;
            }

            vertices_.push_back( v );
        }




        /** Parses a normal coordinate.
        */
        void OBJ_File::normal( void )
        {
            float x, y, z;
            //          string dummy;
            file_ >> x;
            file_ >> y;
            file_ >> z;

            glm::vec3 v = glm::normalize( glm::vec3( x, y, z ) );
            if( tracing_ )
            {
                trace_
                    << "Read normal: ("
                    << x << ") (" << y << ") (" << z << ")\n"
                    << glm::to_string( v ) << endl;
            }

            normals_.push_back( v );
            //            getline( file_, dummy ); /// << may cause problems later.
            //           file_.ignore();
        }



        /** Parses a texture coordinate.
        */
        void OBJ_File::tex_coord( void )
        {
            float u, v;
            //         string dummy;
            file_ >> u;
            file_ >> v;

            glm::vec2 norm(u, v);
            if( tracing_ )
            {
                trace_
                    << "Read texture: ("
                    << u << ") (" << v << ")\n"
                    << glm::to_string( norm ) << endl;
            }


            textures_.push_back( norm );
            //       getline( file_, dummy );
            //        file_.ignore();
        }


        /** Discards the entire current line, which has been determined to be
         * a comment.
         */
        void OBJ_File::comment( void )
        {
            /*
               char x;
               file_ >> x;
               while( x != '\n' )
               {
               file_ >> x;
               }
            //file_.ignore();
            */
            string x;
            getline( file_, x );
        }







        /** Inserts all of the verticies into the provided Vertex_Array.
         * \param va The Vertex_Array.
         * \param c Decides whether or not randomized vertex colors should be
         * used.
         */
        void OBJ_File::fill( Vertex_Array& va, bool c )
        {
            if( tracing_ )
            {
                trace_
                    << " &&&&&&&&&&&&&\n"
                    << "&&& LOADING &&&\n"
                    << " &&&&&&&&&&&&&\n" 
                    << "&&& # faces &&&\n"
                    << faces_.size() << "\n"
                    << " &&&&&&&&&&&&" << endl;
            }

            va.pre_size( faces_.size() );

            for( unsigned i = 0; i < faces_.size(); i++ )
            {
                Index_Set* is = faces_[i];
                glm::vec3 vert;
                glm::vec4 color;
                if( !c )
                {
                    vert = vertices_[is->v];
                    color = glm::vec4(
                            normals_[is->n].x,
                            normals_[is->n].y,
                            normals_[is->n].z,
                            1.0f
                            );
                }
                else
                {
                    vert = vertices_[is->v];
                    color= to_vec_color( Color::random_color() | 0xFF );
                }

                if( tracing_ )
                {
                    trace_
                        << i << "\tpos  : " << glm::to_string( vert ) << "\n"
                        << i << "\tcolor: " << glm::to_string( color ) << endl;
                }

                va.add( Vertex( vert, color ) );
                is = NULL;
            }
            va.done();
        }





        /**  Resets the obj loader to its initial state.  All read data will be
         * deleted.
         */
        void OBJ_File::reset( void )
        {
            close();
            stop_trace();

            if( obj_name_ )
            {
                delete obj_name_;
            }

            for( unsigned i = 0; i < faces_.size(); i++ )
            {
                if( faces_[i] )
                {
                    delete faces_[i];
                }
            }

            vertices_.resize(0);
            textures_.resize(0);
            normals_.resize(0);
            line_ = 0;
        }




        /**  Outputs a trace of the obj parsing into a text file for debugging.
         * \param name The name of the file to be output to.
         */
        void OBJ_File::trace( const string& name )
        {
            trace_.open( name.c_str() );
            tracing_ = true;
        }

        /**  Stops debug tracing if it's being used.
         */
        void OBJ_File::stop_trace( void )
        {
            if( trace_.is_open() )
            {
                trace_.close();
            }
            tracing_ = false;
        }


        /** Closes the obj file being read.
         */
        void OBJ_File::close( void )
        {
            if( filename_ )
            {
                delete filename_;
                filename_ = NULL;
                file_.close();
            }
        }


    } //OBJ namespace.

} //Model namespace.
