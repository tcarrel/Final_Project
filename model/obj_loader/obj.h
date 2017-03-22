/**
 * 
 * \file obj.h
 * \author Thomas R. Carrel
 */


#ifndef  _OBJ_LOADER_H_
# define _OBJ_LOADER_H_

//  This class should only be getting used during loading so its speed is not
// absolutely critical, so stl containers are sufficient.
# include<iostream>
using std::string;
# include<fstream>
# include<vector>
using std::vector;
# include<map>
using std::map;




# include<glm/glm.hpp>


#include "OBJ_except.h"
#include "model_list.h"
#include "../model.h"

class Shader;

namespace Model
{
    class Model;
    class Mesh;
    class Vertex_Array;
    class Vertex;

    namespace OBJ
    {
        class Model_list;

        /** This class takes a wavefront .obj file and loads it into a
         * Vertex_Array object.
         */
        class OBJ_File
        {
            public:
                OBJ_File( void );
                ~OBJ_File( void );

                /**  Opens an .obj file.
                 * \param f The filename.
                 */
                inline void open( const char* f )
                { filename_ = new string( f ); file_.open( f ); }
                /**  Opens an .obj file.
                 * \param s The filename.
                 */
                inline void open( const string& s )
                { open( s.c_str() ); }

                void parse( void )
                    throw(  OBJ_Exception );
                void fill(  Vertex_Array&, bool );
                void reset( void );
                void close( void );
                void trace( const string& );
                void stop_trace( void );
                glm::vec3 size(  void );
                float max_dim(   void );


                Mesh* load_file( const string&, Shader*, bool, GLfloat )
                    throw(  OBJ_Exception );

            private:

                /**  Condition of the input file stream.
                 */
                inline bool good( void )
                { return file_.good(); }

                /**  Checks whether or not a file is opened.
                 */
                inline bool is_open( void )
                { return file_.is_open(); }

                /**  Checks if eof has been read.
                 */
                inline bool eof( void )
                { return file_.eof(); }

                struct Index_Set
                {
                    int v = 0;
                    int t = 0;
                    int n = 0;
                };

                struct Range{
                    string      name;
                    unsigned    start;
                    unsigned    end;
                };

                void add_mesh();
//                void fill( GLuint, bool );

                void vertex();
                void tex_coord();
                void normal();
                void v();
                void g();
                void f();
                void m();
                void o();
                void s();
                void u();
                void comment();

                void measure( float, float, float );

                /**  Returns the next character to be read from the file
                 * without popping it from the queue.
                 */
                inline char peek( void ) { return file_.peek(); }

                std::ifstream   file_; ///< Input file stream.

                std::ofstream   trace_;
                bool            tracing_;

                vector<glm::vec3> vertices_;
                vector<glm::vec2> textures_;
                vector<glm::vec3> normals_;

                vector<Index_Set*> faces_;

                string* filename_; ///< The name of the file being read, mostly
                                   ///< for debugging purposes.
                string* obj_name_; ///< The name of the object.

                unsigned line_; ///< The previous line number;

                GLfloat     size_[3]; 
                GLfloat*    min_;
                GLfloat*    max_;

                Mesh*       top_mesh_;
                GLuint      mesh_qty_;
                Vertex_Array*
                            cur_va_;

                Model_list  m_list_;

                bool        color_by_;
                bool        already_loaded_;
        };

    } // OBJ namespace.

} // Model namespace.

#endif
