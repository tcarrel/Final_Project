




#include<fstream>
using std::ifstream;

#include<string>
using std::string;

#include<vector>
using std::vector;

#include "obj.h"


#ifndef  _LIST_LOADER_H_
# define _LIST_LOADER_H_

#include<glm/glm.hpp>

namespace Model
{    
    class Scene_Graph;

    namespace OBJ
    {
        class World_Loader
        {
            public:
                World_Loader( Scene_Graph* );
                ~World_Loader( void );

                bool operator()( const string& );


                void get_errors( string*, int* );
            private:

                void add_error_msg( string& );

                static Scene_Graph*         sg_;
                static vector<string*>*     error_msgs_;
        };

    } // OBJ namespace.
} // Model namespace.


#endif
