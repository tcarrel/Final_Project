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
#include "../../shader_program.h"

#include "../../tracking_list.h"

#include<iostream>
using std::istream;
using std::endl;

#include<sstream>
using std::stringstream;

#include<cstdio>
#include<cstdlib>
#include<cctype>
#include<cfloat>
#include<cmath>

#include<glm/ext.hpp>

#define GLM_INCLUDED
#include "../../helper_functions.h"
#undef GLM_INCLUDED
// Local helper functions.





namespace Model
{
    namespace OBJ
    {
        /** Generic ctor.
         */
        OBJ_File::OBJ_File( void ) :
            trace_(NULL),
            filename_(NULL),
            obj_name_(NULL),
            line_(0),
            min_(NULL),
            max_(NULL),
            top_mesh_(NULL),
            mesh_qty_(0),
            color_by_(true),
            already_loaded_(false),
            loading_(false)
        {
            size_[0] = size_[1] = size_[2] = 0.0f;
            trace_ = new std::ofstream("/dev/null");
        }





        /** Dtor
         */
        OBJ_File::~OBJ_File( void )
        {
            reset();
            stop_trace();
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
                    file_->ignore();
                }

                switch( peek() )
                {
                    case '#': //comment
                        comment( *file_ );
                        break;
                    case 'v':
                        v( *file_ );
                        break;
                    case 'o':
                        //fallthrough..
                    case 'g':
                        g_or_o( *file_ );
                        break;
                    case 'f':
                        f( *file_ );
                        break;
                    case 'm':
                        m( *file_ );
                        break;
                    case 's':
                        s( *file_ );
                        break;
                    case 'u':
                        u( *file_ );
                        break;
                    default:
                        ; // Do nothing.
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
        void OBJ_File::v( std::istream& file )
        {
            string s;

            file >> s;

            if( s == "v" )
            {
                vertex( file );
                return;
            }

            if( s == "vt" )
            {
                tex_coord( file );
                return;
            }

            if( s == "vn" )
            {
                normal( file );
                return;
            }

            if( s == "vp" )
            {
                if( trace_ )
                {
                    *trace_ << "### Paramaterized ###" << endl;
                }
                comment( file );
            }


            fprintf( stderr,
                    ".obj parsing error.\n"
                    "Discarding current line.\n"
                    "Model, file <%s>, may not render correctly.\n",
                    filename_->c_str()
                   );
            comment( file );
        }





        /** Parses an 'f' line.
        */
        void OBJ_File::f( std::istream& file )
        {
            string v;
            file >> v;

            if( trace_ )
            {
                *trace_
                    << "==============================================\n"
                    << "$$$ Read Face:\n";
            }

            for( int j = 0; j < 3; j++ )
            {
                int val[3];
                Index_Set*  index   = new Index_Set;

                faces_.push_back( index );

                file >> val[0];
                if( peek() != ' ' )
                {
                    file.ignore();
                }
                else
                {
                    index->v = val[0];
                    index = NULL;
                    continue;
                }

                if( isdigit( peek() ) )
                {
                    file >> val[1];
                }
                else
                {
                    val[1] = 0;
                }
                file.ignore();
                file >> val[2];            

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

                if( trace_ )
                {
                    *trace_ << val[0] << "/" << val[1] << "/" << val[2] << "\n";
                }
                glm::vec3 vert = vertices_[index->v];
                glm::vec4 color;
                if( !color_by_ )
                {
                    float x, y, z;
                    x = normals_[index->n].x;
                    y = normals_[index->n].y;
                    z = normals_[index->n].z;
                    
                    x = (x < 0.0f) ? 0.0f : x;
                    x = (x > 1.0f) ? 1.0f : x;
                    y = (y < 0.0f) ? 0.0f : y;
                    y = (y > 1.0f) ? 1.0f : y;
                    z = (z < 0.0f) ? 0.0f : z;
                    z = (z > 1.0f) ? 1.0f : z;
                    /*
                    factor  = x * x;
                    factor += y * y;
                    factor += z * z;
                    factor = sqrt(factor);
                    */

                    color = glm::vec4( x, y, z, 1.0f );
                }
                else
                {
                    color= to_vec_color( Color::random_color() | 0xFF );
                }
                glm::vec3 normal = normals_[index->n];

                if( trace_ )
                {
                    *trace_
                        << "\tpos  : " << glm::to_string( vert ) << "\n"
                        << "\tcolor: " << glm::to_string( color ) << endl;
                }

                cur_va_->add( Vertex( vert, color, normal ) );



                //Index set has already been pushed onto the vector.
                index = NULL;
            }

            if( trace_ )
            {
                *trace_ << endl;
            }
        }




        /** Parses an 'm' line.  Not implemented yet, so they are just
         * ignored.
        */
        void OBJ_File::m( std::istream& file )
        {
            if( trace_ )
            {
                *trace_ << "### m ###" << endl;
            }
            comment( file );
        }





        /** Parses a 'g' or an 'o' line.
        */
        void OBJ_File::g_or_o( std::istream& file )
        {
            if( !obj_name_ )
            {
                obj_name_ = new string;
            }

            file >> *obj_name_;
            file >> *obj_name_;

            add_mesh();

            if( trace_ )
            {
                *trace_ << "Object Name:  " << *obj_name_ << endl;
            }
        }





        /** Parses an 's' line.  Not implemented yet, so they are just
         * ignored.
         */
        void OBJ_File::s( std::istream& file )
        {
            if( trace_ )
            {
                *trace_ << "### s ###" << endl;
            }
            comment( file );
        }





        /** Parses a 'u' line.  Not implemented yet, so they are just
         * ignored.
         */
        void OBJ_File::u( std::istream& file )
        {
            if( trace_ )
            {
                *trace_ << "### u ###" << endl;
            }
            comment( file );
        }





        /** Parses a single vertex coordinate, discards the w-coordinate
         * since that always needs to be set to 1.
         */
        void OBJ_File::vertex( std::istream& file )
        {
            float x, y, z;
            file >> x;
            file >> y;
            file >> z;

            glm::vec3 v( x, y, z );
            if( trace_ )
            {
                *trace_
                    << "Read vertex: ("
                    << x << ") (" << y << ") (" << z << ")\n"
                    << glm::to_string( v ) << endl;
            }

            vertices_.push_back( v );

            measure( x, y, z );
        }





        /** Parses a normal coordinate.
        */
        void OBJ_File::normal( std::istream& file )
        {
            float x, y, z;
            //          string dummy;
            file >> x;
            file >> y;
            file >> z;

            glm::vec3 v = glm::normalize( glm::vec3( x, y, z ) );
            if( trace_ )
            {
                *trace_
                    << "Read normal: ("
                    << x << ") (" << y << ") (" << z << ")\n"
                    << glm::to_string( v ) << endl;
            }

            normals_.push_back( v );
        }






        /** Parses a texture coordinate.
        */
        void OBJ_File::tex_coord( std::istream& file )
        {
            float u, v;
            //         string dummy;
            file >> u;
            file >> v;

            glm::vec2 norm(u, v);
            if( trace_ )
            {
                *trace_
                    << "Read texture: ("
                    << u << ") (" << v << ")\n"
                    << glm::to_string( norm ) << endl;
            }

            textures_.push_back( norm );
        }






        /** Discards the entire current line, which has been determined to be
         * a comment.
         */
        void OBJ_File::comment( std::istream& file )
        {
            string x;
            getline( file, x );
            if( trace_ )
            {
                *trace_ << "Comment: " << x << endl;
            }
        }






        /**  Resets the obj loader to its initial state.  All read data will be
         * deleted.
         */
        void OBJ_File::reset( void )
        {
            close();

            if( obj_name_ )
            {
                delete obj_name_;
                obj_name_ = NULL;
            }

            for( unsigned i = 0; i < faces_.size(); i++ )
            {
                if( faces_[i] )
                {
                    delete faces_[i];
                    faces_[i] = NULL;
                }
            }
            faces_.clear();

            vertices_.clear();
            textures_.clear();
            normals_.clear();
            line_ = 0;

            if( max_ )
            {
                delete [] max_;
                max_ = NULL;
            }

            if( min_ )
            {
                delete [] min_;
                min_ = NULL;
            }
            size_[0] = size_[1] = size_[2] = 0.0f;

            top_mesh_ = NULL;
            mesh_qty_ = 0;

            return;
        }





        /**  Outputs a trace of the obj parsing into a text file for debugging.
         * \param name The name of the file to be output to.
         */
        void OBJ_File::trace( const string& name )
        {
            if( !trace_ )
            {
                trace_ = new std::ofstream( name.c_str() );
            }
            else
            {
                trace_->close();
                trace_->open( name.c_str() );
            }
        }





        /**  Stops debug tracing if it's being used.
        */
        void OBJ_File::stop_trace( void )
        {
            if( trace_ )
            {
                trace_->close();
                delete trace_;
                trace_ = NULL;
            }
            trace_ = new std::ofstream("/dev/null");
        }





        /** Closes the obj file being read.
        */
        void OBJ_File::close( void )
        {
            if( !loading_ && filename_ )
            {
                delete filename_;
                filename_ = NULL;
                file_->close();
                delete file_;
                file_ = NULL;
            }
        }





        /** Records the min and max values along each axis.
         * \param x X-axis value.
         * \param y Y-axis value.
         * \param z Z-axis value.
         */
        void OBJ_File::measure( const float& x, const float& y, const float& z )
        {
            //Minimums
            if( !min_ )
            {
                min_ = new float[3];
                min_[0] = min_[1] = min_[2] = FLT_MAX;
            }

            if( x < min_[0] )
            {
                min_[0] = x;
            }
            if( y < min_[1] )
            {
                min_[1] = y;
            }
            if( z < min_[2] )
            {
                min_[2] = z;
            }

            //Maximums
            if( !max_ )
            {
                max_ = new float[3];
                max_[0] = max_[1] = max_[2] = FLT_MIN;
            }

            if( x > max_[0] )
            {
                max_[0] = x;
            }
            if( y > max_[1] )
            {
                max_[1] = y;
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

            Mesh* mesh = NULL;
            mesh = m_list_.get(name);
            bool already_loaded_ = mesh != NULL;

            if( !already_loaded_ )
            {
                if( trace_ )
                {
                    *trace_ << "Creating new mesh, name: " << name << endl;
                }
                mesh = new Mesh( name, GL_TRIANGLES );
                m_list_.add( mesh->name(), mesh );
            }

            cur_va_     = mesh->get_array();

            if( mesh_qty_ == 0 )
            { 
                top_mesh_   = mesh;
                mesh_qty_   = 1;
                return;
            }

            top_mesh_->add_child( mesh );
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
            fprintf( stderr, "###%s, %f\n", filename.c_str(), size );
            open( filename );
            loading_ = true;

            reset();

            color_by_ = co;
            parse();

            top_mesh_->set_shader( shader );
            top_mesh_->set_size( size, max_dim() );
            top_mesh_->done();

            loading_ = false;
            close();

            return top_mesh_;
        }

    } //OBJ namespace.

} //Model namespace.
