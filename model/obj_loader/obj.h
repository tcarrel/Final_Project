/**
 * 
 * \file obj.h
 * \author Thomas R. Carrel
 */


#ifndef  _OBJ_LOADER_H_
# define _OBJ_LOADER_H_

# include<iostream>
using std::string;

# include<vector>
using std::vector;

# include<map>
using std::map;

# include<glm/glm.hpp>


namespace Model
{
    class Mesh;
    class Vertex_Array;
    class Vertex;

    namespace OBJ
    {

        class OBJ_Exception;

        /** This class takes a wavefront .obj file and loads it into a
         * Vertex_Array object.
         */
        class OBJ_File
        {
            public:
                OBJ_File( string, Vertex_Array* );

            private:
                void parse( void ) throw( OBJ_Exception );

                map<string, vector<glm::vec3>> vertices_;
                map<string, vector<glm::vec3>> normals_;

                vector<string> groups_;
                vector<string> material_files_;

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
