/** *
 * \file world_loader.cpp
 * \author Thomas R. Carrel
 *
 *
 */







#include "world_loader.h"

#include "../scene_graph.h"
#include "../sg_setup.h"
#include "../mesh.h"

#include "../../shaders.h"
#include "../../shader_program.h"
#include "../../helper_functions.h"

#include "../../app/window.h"

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



        /**  Sets up the world loader.
         * @param w The current window.
         */
        World_Loader::World_Loader( App::Window* w ) :
            window_( w ), file_( NULL ), skybox_is_loaded_( false )
        {}



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
                Scene_Graph*&       scene,
                bool                coloring = false )
        {
            std::string path = p + "/";

            int qty = 0;
            std::string  filename = "";

            char input_type = 0;

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

            scene_graph_setup();
            scene = sg_;

            //            obj_ld_.trace( "_obj.trace" );
            while( !( *file_ >> input_type).eof() )
            {
                print_option( input_type );
                switch( input_type )
                {
                    case '#': // Comment
                        getline( *file_, filename );
                        fprintf( stderr, "(Comment) %s\n", filename.c_str() );
                        filename = "";
                        break;
                    case 'P': // shader (P)rogram
                        fprintf( stderr, "Shader\n" );
                        load_shader();
                        break;
                    case 'S': // (S)kybox
                        fprintf( stderr, "Skybox\n" );
                        load_skybox();
                        break;
                    case 'O': // (O)bject file.
                        fprintf( stderr, "Object File\n" );
                        load_object( path, coloring );
                        break;
                    default:
                        fprintf( stderr, "Unknown\n" );
                        break;
                }

            }
            obj_ld_.stop_trace();

            file_->close();
            delete file_;
            file_ = NULL;
            return false;
        }






        /** Loads and compiles a shader program.
        */
        void World_Loader::load_shader( void )
        {
            string fname;
            cur_shader_ = new Shader;
            int qty;
            *file_ >> qty;

            for( int i = 0; i < qty; i++ )
            {
                if( i < (qty - 1) )
                {
                    getline( *file_, fname, ',' );
                }
                else
                {
                    getline( *file_, fname );
                }

                if( fname[0] == '#' )
                {
                    fname = "";
                    continue; // Comment
                }

                /*
                string shdr_name = shader_filename_to_struct_name( fname );
                fprintf( stderr, "#%i %s\n", i, shdr_name.c_str() );

                cur_shader_->add_code(
                        get_shader( shdr_name ) );
                        */
                cur_shader_->add_code( fname );
            }
            if( cur_shader_->compile( "World_Loader" ) == ERROR )
            {
                fprintf(
                        stderr,
                        "World loader could not compile shaders.\n\n"
                       );

            }
        }





        /** Loads an .obj file.
        */
        void World_Loader::load_object(
                const std::string& path,
                bool coloring ) throw( World_Exception )
        {
            std::string filename;
            GLfloat floats[3];
            GLchar option = '^';
            floats[0] = floats[1] = floats[2] = 0.0f;

            getline( *file_, filename, ',' );

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
                if( i < 2 )
                {
                    file_->ignore();
                }
            }

            fprintf( 
                    stderr,
                    "position = ( %f, %f, %f )\n",
                    floats[0], floats[1], floats[2]
                   );
            mdl->set_position( floats[0], floats[1], floats[2] );

            mdl->add( msh );

            if( file_->peek() != '\n' )
            {
                file_->ignore();
                *file_ >> option;
                fprintf( stderr, "Char=%c\n", option );
                switch( option )
                {
                    case 'M': //Mirrored
                        //fallthrough.
                    case 'm':
                        mdl->set_reflect(
                                sg_->get_mirror_prog(),
                                sg_->get_skybox_ptr() );
                        break;
                    case 'T': //Transparent
                        //fallthrough
                    case 't':
                        break;
                    case 'F': //Fresnel
                        //fallthrough
                    case 'f':
                        break;
                    default:
                        fprintf( stderr, "Invalid render mode.\n" );
                }
            }

            sg_->add_models( &mdl, 1 );

            obj_ld_.reset();
        }





        /** Loads a skybox.
        */
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
            skybox_is_loaded_ = true;
        }





        /** Loads the initial settings for a scene graph.
        */
        void World_Loader::scene_graph_setup( void )
        {
            SG_Setup setup;
            bool is_pers;

            GLfloat x = 0, y = 0, z = 0;

            //Eye position.
            *file_ >> x;
            file_->ignore();
            *file_ >> y;
            file_->ignore();
            *file_ >> z;
            setup.eye_position( x, y, z );

            //Lookat.
            *file_ >> x;
            file_->ignore();
            *file_ >> y;
            file_->ignore();
            *file_ >> z;
            setup.target( x, y, z );

            //Up direction.
            *file_ >> x;
            file_->ignore();
            *file_ >> y;
            file_->ignore();
            *file_ >> z;
            setup.up_dir( x, y, z );

            //Perspective or Orthographic
            *file_ >> is_pers;
            file_->ignore();
            if( is_pers )
            {
                GLfloat fov, near, far;

                *file_ >> fov;
                file_->ignore();
                *file_ >> near;
                file_->ignore();
                *file_ >> far;

                setup.perspective( fov, near, far, window_->aspect() );
            }
            else
            {
                GLfloat left, right, up, down, back, front;

                *file_ >> left;
                file_->ignore();
                *file_ >> right;
                file_->ignore();
                *file_ >> up;
                file_->ignore();
                *file_ >> down;
                file_->ignore();
                *file_ >> back;
                file_->ignore();
                *file_ >> front;

                setup.orthographic( left, right, up, down, back, front );
            }
            file_->ignore();

            setup.window( window_ );

            sg_ = Scene_Graph::ctor( &setup );
        }



        /*
           void World_Loader::get_command( std::string& cmd, std::string& tail )
           {
           size_t paren = 1 + cmd.find_first_of( '(' );

           tail = cmd.substr( paren );
           cmd = cmd.substr( 0, paren );
           }
           */

    } //OBJ namespace.

} //Model namespace.

