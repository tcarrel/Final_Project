/**
 *
 * \file world_loader.cpp
 * \author Thomas R. Carrel
 *
 *
 */






#include "world_loader.h"

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










        void World_Loader::get_errors( string* msgs, unsigned* qty )
        {
            if( !qty )
            {
//                add_error_msg( "
                return;
            }


            if( !msgs )
            {
                if( qty )
                {
                    *qty = (error_msgs_) ? error_msgs_->size() : 0;
                }
            }
            else
            {
                auto iter = error_msgs_->begin();
                for( unsigned i = 0; i < *qty; i++, iter++ )
                {
                    msgs[i] = **iter;
                }
                delete error_msgs_; 
                error_msgs_ = NULL;
            }
        }











        void World_Loader::add_error_msg( unsigned erno, const string& txt )
        {
            if( !error_msgs_ )
            {
                error_msgs_ = new vector<string*>;
            }

            string* temp = error_num_to_msg( erno, txt );
            error_msgs_->push_back( new string(*temp) );
            delete temp;
            temp = NULL;
        }








        /**  Generates an error message string.
         * \param erno The error number.
         */
        string* World_Loader::error_num_to_msg(
                unsigned erno,
                const string&  )
        {
            //"\033[0,31mWORLD LOADING ERROR:\033[0m\t"
            char* buffer = new char[256];
            string* msg  = NULL;
            switch( erno )
            {
                default:
                    sprintf( buffer,
                            "\033[0,31mWORLD LOADING ERROR (0x%x):\033[0m\t"
                            "undefined error.\n", erno );
                    msg = new string( buffer );
                    break;
                case 0:
                    delete buffer; 
                    return NULL;
                case 0xDEADBEEF:
                    sprintf( buffer,
                            "\033[0,31mWORLD LOADING ERROR (0x%x):\033[0m\t"
                            "get_errors() arguments (2) must not be NULL.\n",
                            erno );
                    msg = new string( buffer );
                    break;
            }

            delete buffer;
            return msg;
        }










        bool World_Loader::operator()( const string& filename )
        {
            ///

            return false;
        }





    } //OBJ namespace.

} //Model namespace.

