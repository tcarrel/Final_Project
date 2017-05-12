/** *
 * \file world_loader.cpp
 * \author Thomas R. Carrel
 *
 *
 */







#include "obj.h"
#include "world_loader.h"

#include "../scene_graph.h"
#include "../sg_setup.h"
#include "../mesh.h"
#include "../instanced.h"

#include "../../shaders.h"
#include "../../shader_program.h"
#include "../../helper_functions.h"

#include "../../app/window.h"

#include<cctype>

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
                bool                coloring = false
                )
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
            file_->open( (path + level_filename).c_str() );

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
                    case 'I': // (I)nstanced.
                        fprintf( stderr, "Instanced\n" );
                        load_instanced( path, coloring );
                        break;
                    default:
                        fprintf(
                                stderr,
                                "Unknown, '%c' was read.\n",
                                input_type );
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
            GLfloat scale;
            GLchar option = '^';
            glm::vec3*  position = new glm::vec3;
            glm::vec3*  rotation = new glm::vec3;

            getline( *file_, filename, ',' );

            filename = path + filename;

            *file_ >> scale; //scale
            file_->ignore();

            read_vec3( *position );
            file_->ignore();
            read_vec3( *rotation );

            Model* mdl = new Model;
            Mesh*  msh = obj_ld_.load_file(
                    filename,
                    cur_shader_,
                    coloring,
                    scale );

            fprintf(
                    stderr,
                    "filename:\t%s\nscale:\t\t%f\n",
                    filename.c_str(),
                    scale );
            fprintf(
                    stderr,
                    "position = ( %f, %f, %f )\n",
                    position->x, position->y, position->z );



            mdl->set_position( *position );
            mdl->rotate( *rotation );

            delete position; position = NULL;
            delete rotation; rotation = NULL;

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
                        mirrored( mdl );
                        break;
                    case 'T': //Transparent
                        //fallthrough
                    case 't':
                        transparent( mdl );
                        break;
                    case 'F': //Fresnel
                        //fallthrough
                    case 'f':
                        fresnel_transparency( mdl );
                        break;
                    default:
                        fprintf( stderr, "Invalid render mode.\n" );
                        while( file_->peek() != '\n' )
                        {
                            file_->ignore();
                        }
                }
            }

            sg_->add_models( &mdl, 1 );

            obj_ld_.reset();
        }




        /**  Sets a model to be rendered as reflective.
         * @param mod A pointer to the model.
         */
        void World_Loader::mirrored( Model* mod )
        {
            mod->set_reflect( sg_->get_mirror_prog(), sg_->get_skybox_ptr() );
        }





        /**  Sets a model to be rendered with pure refraction.
         * @param mod A pointer to the model.
         */
        void World_Loader::transparent( Model* mod )
        {
            GLfloat refr; //Index of refraction;

            if( isdigit( file_->peek() ) )
            {
                *file_ >> refr;
            }
            else
            {
                string out, in;
                getline( *file_, out, ',' );
                *file_ >> in;
                refr = get_refraction_ratio( out, in );
            }
            mod->set_refract(
                    sg_->get_refract_prog(),
                    sg_->get_skybox_ptr(),
                    refr );
        }





        /**
         */
        void World_Loader::fresnel_transparency( Model* mod )
        {
            //Indices of reflection.
            GLfloat n1, n0; 
            if( isdigit( file_->peek() ) )
            {
                *file_ >> n0;
                file_->ignore();
                *file_ >> n1;
                mod->set_fresnel(
                        sg_->get_fresnel_prog(),
                        sg_->get_skybox_ptr(),
                        n0, n1 );
            }
            else
            {
                string out, in;
                getline( *file_, out, ',' );
                *file_ >> in;
                n0 = get_refractive_index( out );
                n1 = get_refractive_index( in );
                mod->set_fresnel(
                        sg_->get_fresnel_prog(),
                        sg_->get_skybox_ptr(),
                        n0 / n1,
                        (n0 - n1) / (n0 + n1 ) );
            }
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





        /**  Read in a vec3.
         * @param vec The vector to read into.
         */
        void    World_Loader::read_vec3( glm::vec3& vec )
        {
            *file_ >> vec.x;
            file_->ignore();
            *file_ >> vec.y;
            file_->ignore();
            *file_ >> vec.z;
        }





        void    World_Loader::load_instanced( const string& path, bool col )
        {
            string model_file = "";
            GLint qty;
            GLfloat offset, radius, scale;

            getline( *file_, model_file, ',' );
            model_file = path + model_file;
            *file_ >> qty;
            file_->ignore();
            *file_ >> radius;
            file_->ignore();
            *file_ >> offset;
            file_->ignore();
            *file_ >> scale;

            fprintf( stderr,
                    "Instanced (%s)\n"
                    "\tQuantity:\t%i\n"
                    "\tRadius:\t\t%f\n"
                    "\tOffset:\t\t%f\n"
                    "\tScale:\t\t%f\n",
                    model_file.c_str(),
                    qty, radius, offset, scale );

//            Mesh* msh = obj_ld_.load_file( model_file, NULL, col, 1 );

            sg_->set_instanced( new Instanced(
                    qty,
                    radius,
                    offset,
                    scale,
                    model_file,
                    &obj_ld_,
                    col ) );
        }


    } //OBJ namespace.

} //Model namespace.

