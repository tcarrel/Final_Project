/**
 *
 * \file model_list.h
 * \author Thomas R. Carrel
 *
 *
 */

#include<unordered_map>
using std::unordered_map;
#include<vector>
using std::vector;
#include<string>
using std::string;


namespace Model
{
    class Mesh;

    namespace OBJ
    {
        /** A place to store and retrieve all previously loaded meshes, to
         * allow for instanced rendering.
         */
        class Model_list
        {
            public:
                ~Model_list( void ); ///< Dtor.

                Mesh* get_mesh( const string& );
                void add_mesh( Mesh* );
            private:
                /** Maps the names to the pointer. */
                static unordered_map<string, Mesh*>     data_; 
                /** Faster than itterating through a map */
                static vector<string>                   names_;
        };
    } // OBJ namepsace.
} //Model namepsace.
