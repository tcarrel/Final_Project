/** *
 * \file world_loader.cpp
 * \author Thomas R. Carrel
 *
 *
 */







#include "world_loader.h"

#include "../scene_graph.h"
#include "../mesh.h"

#include "../../shader_program.h"
#include "../../helper_functions.h"


namespace Model
{
    namespace OBJ
    {

        /** A pointer/reference to the Scene_Graph.
         */
        Scene_Graph* World_Loader::sg_                          =  NULL;
        /** If error messages are generated, this vector is allocated and used
         * to store them.  It can then be freed after the messages are read.
         */
        std::vector<std::string*>* World_Loader::error_msgs_    =  NULL;







        World_Loader::World_Loader( Scene_Graph* sg ) : file_(NULL)
        {
            sg_ = sg;
        }







        World_Loader::~World_Loader( void )
        {
            sg_ = NULL;
            if( file_ )
            {
                if( file_->is_open() )
                {
                    file_->close();
                }
                delete file_;
                file_ = NULL;
            }
        }










        void World_Loader::get_errors( std::string* msgs, unsigned* qty )
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











        void World_Loader::add_error_msg( unsigned erno, const std::string& txt )
        {
            if( !error_msgs_ )
            {
                error_msgs_ = new std::vector<std::string*>;
            }

            std::string* temp = error_num_to_msg( erno, txt );
            error_msgs_->push_back( new std::string(*temp) );
            delete temp;
            temp = NULL;
        }








        /**  Generates an error message string.
         * \param erno The error number.
         */
        std::string* World_Loader::error_num_to_msg(
                unsigned erno,
                const std::string&  )
        {
            //"\033[0,31mWORLD LOADING ERROR:\033[0m\t"
            char* buffer = new char[256];
            std::string* msg  = NULL;
            switch( erno )
            {
                default:
                    sprintf( buffer,
                            "\033[0,31mWORLD LOADING ERROR (0x%x):\033[0m\t"
                            "undefined error.\n", erno );
                    msg = new std::string( buffer );
                    break;
                case 0:
                    delete buffer; 
                    return NULL;
                case 0xDEADBEEF:
                    sprintf( buffer,
                            "\033[0,31mWORLD LOADING ERROR (0x%x):\033[0m\t"
                            "get_errors() arguments (2) must not be NULL.\n",
                            erno );
                    msg = new std::string( buffer );
                    break;
            }

            delete buffer;
            return msg;
        }








        bool World_Loader::operator()(
                const std::string&  p,
                const std::string&  level_filename,
                Shader*             shdr,
                bool                coloring = false )
        {
            std::string path = p + "/";

            int qty = 0;
            std::string  filename = "";

            fprintf(
                    stdout,
                    "Begin loading level\t%s\n",
                    level_filename.c_str() );

            file_ = new std::ifstream;
            file_->open( (path + level_filename + ".cn").c_str() );

            (*file_) >> qty;
            file_->ignore();

            std::vector<Model*> models;

            fprintf( stdout, " Number of models in level:\t%i\n", qty );

            GLfloat scale = 0.0f;
            
            obj_ld_.trace( "_obj.trace" );
            while( !( getline(*file_, filename, ',').eof() ) )
            {
                filename = path + filename;
                (*file_) >> scale;
                file_->ignore();

                fprintf(
                        stderr,
                        "filename:\t%s\nscale:\t\t%f\n",
                        filename.c_str(),
                        scale );

                Model* mdl = new Model;
                Mesh*  msh = obj_ld_.load_file(
                        filename,
                        shdr,
                        coloring,
                        scale );

                mdl->add( msh );

                sg_->add_models( &mdl, 1 );

                obj_ld_.reset();
//                models.push_back( mdl );
//                mdl->add_mesh
            }
            obj_ld_.stop_trace();




            file_->close();
            delete file_;
            file_ = NULL;
            return false;
        }





    } //OBJ namespace.

} //Model namespace.

