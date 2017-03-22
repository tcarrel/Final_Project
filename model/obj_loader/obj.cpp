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
#include "../mesh.h"

#include "../../colors.h"
#include "../../helper_functions.h"
#include "../../shader_program.h"

#include<iostream>
using std::istream;
using std::endl;
#include<sstream>
using std::stringstream;


#include<cstdio>
#include<cstdlib>
#include<cctype>
#include<cfloat>


#include<glm/ext.hpp>

// Local helper functions.







namespace Model
{
    namespace OBJ
    {

        /** Generic ctor.
         */
        OBJ_File::OBJ_File( void ) :
            tracing_(false),
            filename_(NULL),
            obj_name_(NULL),
            line_(0),
            min_(NULL),
            max_(NULL),
            top_mesh_(NULL),
            mesh_qty_(0),
            color_by_(true),
            already_loaded_(false)
        {
            size_[0] = size_[1] = size_[2] = 0.0f;
        }

        /** Dtor
         */
        OBJ_File::~OBJ_File( void )
        {
            reset();
        }




        /**  Initiates parsing of an .obj file.
        */
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

            while( !eof() )
            {
                ++line_;

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
            }
            size_[0] = max_[0] - min_[0];
            size_[1] = max_[1] - min_[1];
            size_[2] = max_[2] - min_[2];

            delete [] max_;
            delete [] min_;
            max_ = min_ = NULL;
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
        void OBJ_File::g( void )
        {
            if( tracing_ )
            {
                trace_ << "### g ###" << endl;
            }
            o();
        }


        /** Parses an 'f' line.
        */
        void OBJ_File::f( void )
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
                glm::vec3 vert;
                glm::vec4 color;
                if( !color_by_ )
                {
                    vert = vertices_[index->v];
                    color = glm::vec4(
                            normals_[index->n].x,
                            normals_[index->n].y,
                            normals_[index->n].z,
                            1.0f
                            );
                }
                else
                {
                    vert = vertices_[index->v];
                    color= to_vec_color( Color::random_color() | 0xFF );
                }

                if( tracing_ )
                {
                    trace_
                        << "\tpos  : " << glm::to_string( vert ) << "\n"
                        << "\tcolor: " << glm::to_string( color ) << endl;
                }

                cur_va_->add( Vertex( vert, color ) );



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

            add_mesh();

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

            measure( x, y, z );
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
            //getline( file_, dummy ); /// << may cause problems later.
            //file_.ignore();
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
        }


        /** Discards the entire current line, which has been determined to be
         * a comment.
         */
        void OBJ_File::comment( void )
        {
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

            if( max_ )
            {
                delete [] max_;
            }

            if( min_ )
            {
                delete [] min_;
            }

            return;
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



        /** Records the min and max values along each axis.
         * \param x X-axis value.
         * \param y Y-axis value.
         * \param z Z-axis value.
         */
        void OBJ_File::measure( float x, float y, float z )
        {
            if( !min_ )
            {
                min_ = new float[3];
                min_[0] = min_[1] = min_[2] = FLT_MAX;
            }

            if( !max_ )
            {
                max_ = new float[3];
                max_[0] = max_[1] = max_[2] = FLT_MIN;
            }

            if( x < min_[0] )
            {
                min_[0] = x;
            }
            if( x > max_[0] )
            {
                max_[0] = x;
            }

            if( y < min_[1] )
            {
                min_[1] = y;
            }
            if( y > max_[1] )
            {
                max_[1] = y;
            }

            if( z < min_[2] )
            {
                min_[2] = z;
            }
            if( z > max_[2] )
            {
                max_[2] = z;
            }

        }




        /** Returns the size of the model.
        */
        glm::vec3 OBJ_File::size( void )
        {
            return glm::vec3( size_[0], size_[1], size_[2] );
        }





        /** Returns the largest dimension of the model.
        */
        float   OBJ_File::max_dim( void )
        {
            float val = size_[0];
            val = (val < size_[1]) ? size_[1] : val;
            return (val < size_[2]) ? size_[2] : val;
        }








        /** Add a mesh to the current load process.
        */
        void OBJ_File::add_mesh( void )
        {
            string name = *filename_ + "^^" + *obj_name_;

            Mesh* mesh = m_list_.get_mesh(name);
            bool already_loaded_ = mesh != NULL;

            if( !already_loaded_ )
            {
                mesh = new Mesh( name, GL_TRIANGLES );
            }

            if( mesh_qty_ == 0 )
            {
                top_mesh_   = mesh;
                cur_va_     = mesh->get_array();
                mesh_qty_   = 1;
                return;
            }

            top_mesh_->add_child( mesh );
            if( !already_loaded_ )
            {
                cur_va_->done();
            }
            cur_va_     = mesh->get_array();
            mesh_qty_++;
            return;
        }






        /**  Load an .obj file.
         * \param filename The path and file to be loaded.
         * \param shader The shader to be used during the rendering of the
         * mesh.
         * \param co Set to true to give a randomized color to each vertex,
         * set to false to use the normal vertex for coloring. (This will not
         * be needed later.)
         * \param size The 'actual' size of the object in centimeters, this
         * allows objects to be modelled at different sizes and the scaled into
         * the coordinate system of this world.  In other words, a traveling
         * 1-unit in this coordinate system is the same as traveling 1-cm in
         * the real world.
         * \return The loaded .obj file.
         */
        Mesh* OBJ_File::load_file(
                const string& filename,
                Shader* shader,
                bool co,
                GLfloat size
                ) throw( OBJ_Exception )
        {
            if( filename == "" )
            {
                throw( OBJ_Exception( "Filename cannot be empty." ) );
            }
            if( !shader )
            {
                throw( OBJ_Exception( "Shader cannot be NULL." ) );
            }
            reset();

            color_by_ = co;
            open( filename );
            parse();

            top_mesh_->set_shader( shader );
            top_mesh_->set_size( size, max_dim() );
            top_mesh_->done();

            return top_mesh_;
        }

    } //OBJ namespace.

} //Model namespace.
