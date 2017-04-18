/** *
 * \file world_loader.cpp
 * \author Thomas R. Carrel
 *
 *
 */







#include "world_loader.h"

#include "../scene_graph.h"
#include "../mesh.h"

#include "../../shaders.h"
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











        void World_Loader::add_error_msg(
                unsigned erno,
                const std::string& txt )
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

            while( file_->peek() == '#' )
            {
                getline( *file_, filename );
                filename = "";
            }
            filename = "";

            (*file_) >> qty;
            file_->ignore();

            std::vector<Model*> models;

            fprintf( stdout, " Number of models in level:\t%i\n", qty );

            GLfloat floats[3];
            floats[0] = floats[1] = floats[2] = 0.0f;

            //            obj_ld_.trace( "_obj.trace" );
            while( !( getline(*file_, filename, ',').eof() ) )
            {
                if( filename[0] == '#' )
                {
                    while( file_->peek() != '\n' )
                    {
                        file_->ignore();
                    }
                    file_->ignore();
                    continue; // Comment
                }

                if( filename == "*SHADERS*" )
                {
                    fprintf( stderr, "Load shaders.\n" );
                    load_shader();
                    continue;
                }

                if( filename == "*SKYBOX*" )
                {
                    fprintf( stderr, "Load skybox.\n" );
                    load_skybox();
                    continue;
                }

                filename = path + filename;
                *file_ >> floats[0];
                file_->ignore();

                fprintf(
                        stderr,
                        "filename:\t%s\nscale:\t\t%f\n",
                        filename.c_str(),
                        floats[0] );

                Model* mdl = new Model;
                Mesh*  msh = obj_ld_.load_file(
                        filename,
                        cur_shader_,
                        coloring,
                        floats[0] );

                for( int i = 0; i < 3; i++ )
                {
                    *file_ >> floats[i];
                    file_->ignore();
                }

                fprintf( 
                        stderr,
                        "position = ( %f, %f, %f )\n",
                        floats[0], floats[1], floats[2]
                       );
                mdl->set_position( floats[0], floats[1], floats[2] );

                mdl->add( msh );

                sg_->add_models( &mdl, 1 );

                obj_ld_.reset();
            }
            obj_ld_.stop_trace();

            file_->close();
            delete file_;
            file_ = NULL;
            return false;
        }






        void World_Loader::load_shader( void )
        {
            string fname;
            cur_shader_ = new Shader;
            int qty;
            *file_ >> qty;
            file_->ignore();

            for( int i = 0; i < qty; i++ )
            {
                getline( *file_, fname );
                if( fname[0] == '#' )
                {
                    fname = "";
                    continue; // Comment
                }

                string shdr_name = shader_filename_to_struct_name( fname );
                fprintf( stderr, "#%i %s\n", i, shdr_name.c_str() );

                cur_shader_->add_code(
                        get_shader( shdr_name ) );

            }
            if( cur_shader_->compile() == ERROR )
            {
                fprintf(
                        stderr,
                        "World loader could not compile shaders.\n\n"
                       );

            }
        }



        void World_Loader::load_skybox( void )
        {
            string r, l, u, d, b, f;
            getline( *file_, r, ',' );
            getline( *file_, l, ',' );
            getline( *file_, u, ',' );
            getline( *file_, d, ',' );
            getline( *file_, b, ',' );
            getline( *file_, f );

            sg_->add_skybox( r, l, u, d, b, f );
        }

    } //OBJ namespace.

} //Model namespace.

