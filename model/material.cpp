




#include "material.h"


#include<fstream>
using std::istream;
using std::ifstream;

#include<cstdio>

//#define DEBUG

#ifdef DEBUG
# include "../function_timer.h"
#endif


void read_color( glm::vec3& color, istream& inf )
{
    inf >> color.r;
    inf >> color.g;
    inf >> color.b;
}


namespace Model
{

    Material::Material( const string& path, const string& n ) :
        path_( new string(path + "/") ),
        filename_( new string(path + "/" + n) ),
        cur_mat_( NULL )
    {
#ifdef DEBUG
        Function_Timer asdjhfgakjhghjafaghg( "Loading material\n", stderr );
#endif
        string command = "";
        ifstream inf;
        inf.open( filename_->c_str() );

        if( !inf.good() )
        {
            fprintf(
                    stderr,
                    "Could not open material file <%s>.\n",
                    filename_->c_str() );
        }


        while( !(inf >> command).eof() )
        {
            switch( command[0] )
            {
                case '#': //comment
                    getline( inf, command );
                    command = "";
                    break;
                case 'n': //newmtl
                    if( newmtl( command, inf ) )
                    {
                        fprintf(
                                stderr,
                                "New material named <%s>.\n",
                                cur_mat_->c_str()
                               );
                    }
                    break;
                case 'N':
                    N( command, inf );
                    break;
                case 'K':
                    K( command, inf );
                    break;
                case 'd':
                    inf >> dissolved_;
                    break;
                case 'i':
                    inf >> illum_;
                    break;
                case 'm':
                    fprintf( stderr, "m\n" );
                    m( command, inf );
                    break;
                default:
                    fprintf(
                            stderr,
                            "Error reading mtl file, <%s>.\n"
                            "\t\"%s\" encountered.\n",
                            filename_->c_str(),
                            command.c_str() );
            }
            command = "";
        }

        delete filename_;
        filename_ = NULL;
        delete path_;
        path_ = NULL;
        if( cur_mat_ )
        {
            delete cur_mat_;
        }
        cur_mat_ = NULL;
    }



    /** Dtor.
    */
    Material::~Material( void )
    {
        if( path_ )
        {
            delete path_;
        }
        if( filename_ )
        {
            delete filename_;
        }
        if( cur_mat_ )
        {
            delete cur_mat_;
        }
        path_ = filename_ = cur_mat_ = NULL;
    }





    /**
    */
    Texture::Texture_base* Material::get_tex( const string& target )
    {
        for( unsigned i = 0; i < mtl_names_.size(); i++ )
        {
            if( *mtl_names_[i] == target )
            {
                return textures_[target];
            }
        }

        return new Texture::Texture_Default;
    }




    bool    Material::newmtl( const string& cmd, istream& inf )
    {
        if( cmd != "newmtl" )
        {
            return false;
        }

        string name;
        inf >> name;

        cur_mat_ = new string( name );

        return true;
    }




    bool Material::N( const string& cmd, istream& inf )
    {
        switch( cmd[1] )
        {
            case 's':
                inf >> spec_exponent_;
                break;
            case 'i':
                inf >> refractive_index_;
                break;
            default:
                return false;
        }
        return true;
    }




    bool Material::K( const string& cmd, istream& inf )
    {
        switch( cmd[1] )
        {
            case 'a':
                read_color( ambient_, inf );
                break;
            case 'd':
                read_color( diffuse_, inf );
                break;
            case 's':
                read_color( specular_, inf );
                break;
            case 'e':
                read_color( emissive_, inf );
                break;
            default:
                return false;
        }
        //probably not necessary.
        while( inf.peek() != '\n' )
        {
            inf.ignore();
        }
        return true;
    }




    bool Material::m( const string& cmd, istream& inf )
    {
        string path_file;
        char ignore_msg[] = "%s, not implemented, ignoring.\n";

        if( !cur_mat_ )
        {
            fprintf( stderr, "No named material.\n" );
            return false;
        }

        fprintf( stderr, "%s m() functions.\n", cmd.c_str() );

        if( cmd == "map_Kd" )
        {
            inf >> path_file;
            path_file = *path_ + path_file;

            fprintf(
                    stderr,
                    "Load texture: %s\n",
                    path_file.c_str() );

            Texture::Texture_2D* tex = new Texture::Texture_2D( path_file );
            textures_[*cur_mat_] = tex;
            tex = NULL;
            return true;
        }

        if( cmd == "map_Bump" )
        {
            fprintf(
                    stderr,
                    ignore_msg,
                    "map_Bump" );

            inf >> path_file;

            fprintf(
                    stderr,
                    "Load texture: %s\n",
                    path_file.c_str() );

            return false;
        }

        fprintf(
                stderr,
                ignore_msg,
                cmd.c_str() );
        inf >> path_file;

        return false;
    }
} //Model namespace.
