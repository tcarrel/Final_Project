






#include "list_loader.h"

#include "../scene_graph.h"



namespace Model
{
    namespace OBJ
    {

        /** A pointer/reference to the Scene_Graph.
         */
        Scene_Graph* World_Loader::sg_               =   NULL;
        /** If error messages are generated, this vector is allocated and used
         * to store them.  It can then be freed after the messages are read.
         */
        vector<string*>* World_Loader::error_msgs_   =   NULL;







        World_Loader::World_Loader( Scene_Graph* sg )
        {
            sg_ = sg;
        }







        World_Loader::~World_Loader( void )
        {
            sg_ = NULL;
        }





        bool World_Loader::operator()( const string& filename )
        {

            return false;
        }





        void get_errors( string* msgs, int* qty )
        {
            if( !(msgs || qty) )
            {
                return;
            }
        }
    } //OBJ namespace.
} //Model namespace.
