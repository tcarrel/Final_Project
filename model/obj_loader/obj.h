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

namespace Model
{
    class Mesh;
    class Vertex_Array;
    class Vertex;

    namespace OBJ
    {
        /** This class takes a wavefront .obj file and loads it into a
         * Vertex_Array object.
         */
        class OBJ_File
        {
            public:
                OBJ_File( void );
                OBJ_File( const string& );
                ~OBJ_File( void );

                /**  Opens an .obj file.
                 * \param f The filename.
                 */
                inline void open( const char* f )
                {
                    filename_ = new string( f );
                    file_.open( f );
                }
                /**  Opens an .obj file.
                 * \param s The filename.
                 */
                inline void open( const string& s )
                {
                    open( s.c_str() );
                }

                /**  Condition of the input file stream.
                 */
                inline bool good( void )
                {
                    return file_.good();
                }

                /**  Checks whether or not a file is opened.
                 */
                inline bool is_open( void )
                { return file_.is_open(); }

                /**  Checks if eof has been read.
                 */
                inline bool eof( void )
                { return file_.eof(); }

                /**  Initiates parsing of an .obj file.
                 */
                void parse( void ) throw( OBJ_Exception );

                /**  Initiates parsing of an .obj file.
                 * \param s The name of the .obj file to be read.
                 */
                inline void parse( const string& s )
                { open(s); parse(); }

                /**  Initiates parsing of an .obj file.
                 * \param s The name of the .obj file to be read.
                 */
                inline void parse( const char* s )
                { open(s); parse(); }


                void fill( Vertex_Array&, bool );
                void reset( void );
                void close( void );
                void trace( const string& );
                void stop_trace( void );

            private:

                struct Index_Set
                {
                    int v = 0;
                    int t = 0;
                    int n = 0;
                };

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

                /**  Returns the next character to be read from the file
                 * without popping it from the queue.
                 */
                inline char peek( void ) { return file_.peek(); }

                std::ifstream file_; ///< Input file stream.

                std::ofstream trace_;
                bool          tracing_;

                vector<glm::vec3> vertices_;
                vector<glm::vec2> textures_;
                vector<glm::vec3> normals_;

                vector<Index_Set*> faces_;

//                map<string, vector<glm::vec3>> vertices_;
//                map<string, vector<glm::vec3>> normals_;

//                vector<string*> groups_;
//                vector<string*> material_files_;

                string* filename_; ///< The name of the file being read, mostly
                                   ///< for debugging purposes.
                string* obj_name_; ///< The name of the object.
        };

    } // OBJ namespace.

} // Modle namespace.



#endif
