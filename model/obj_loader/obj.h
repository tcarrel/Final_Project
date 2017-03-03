/**
 * 
 * \file obj.h
 * \author Thomas R. Carrel
 */


#ifndef  _OBJ_H_
# define _OBJ_H_

# include<iostream>
# include<vector>
using std::vector;

# include<glm/glm.hpp>


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
                OBJ_File( std::string, Vertex_Array* );

            private:
                vector<glm::vec3> vertices_;
                vector<glm::vec3> normals_;

                vector<std::string> material_files_;
                

        };
    } // OBJ namespace.
} // Modle namespace.



#endif
