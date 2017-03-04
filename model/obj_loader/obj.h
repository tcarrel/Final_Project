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

                inline void open( const char* f ) { file_.open( f ); }
                inline void open( const string& s ) { open( s.c_str() ); }

                inline bool good() { return file_.good(); }
                inline bool is_open() { return file_.is_open(); }
                inline bool fail() { return file_.fail(); }

                void parse( void ) throw( OBJ_Exception );

            private:

                inline char peek( void ) { return file_.peek(); }

                std::ifstream file_;
                bool opened_;

                Vertex_Array* va_;

                map<string, vector<glm::vec3>> vertices_;
                map<string, vector<glm::vec3>> normals_;

                vector<string*> groups_;
                vector<string*> material_files_;

//                static vector<string*>

                    struct Vert
                    {
                        float x;
                        float y;
                        float z;
                    };
        };

    } // OBJ namespace.

} // Modle namespace.



#endif
