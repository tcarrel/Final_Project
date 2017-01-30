/**
 *
 * glsl_parse.cpp
 *
 *   Copies contents of glsl files into c-code files to be hard-coded and
 * included in the final program as c-style strings.
 *
 *   The only purpose of this program is to allow shaders to be edited with
 * syntax highlighting in vim (or whichever program one chooses.)
 *
 *   "Modifies" the compilation process.
 */




#include<iostream>
using std::string;
using std::cout;
using std::cerr;
using std::endl;

#include<fstream>
using std::ifstream;
using std::ofstream;
using std::ostream;

#include<vector>
using std::vector;

//Debug
#include<cassert>
//using std::assert;

//Add options for different os's.
#include<dirent.h>

const char DQ = '\"';
const char* SHADER_TYPE_NAME = "shader_code";


void insert_comment( ostream& out, char* exec_name )
{
    out <<
        "//\n" <<
        "// filename: shaders.h\n" <<
        "//\n" <<
        "//   Auto-generated header file containing code from all shaders" <<
        "used in this\n" <<
        "// program.  A list of the files used to generated this file can " <<
        "be found at\n" <<
        "// the bottom of this file.\n" <<
        "//\n" <<
        "// file generated by:     " << exec_name << endl <<
        "//\n" <<
        "//\n" << endl << endl << endl;
}


void header_def_start( ostream& out, const char* DEF_TAG )
{
    out << "#ifndef  " << DEF_TAG << "\n"
        << "# define " << DEF_TAG << "\n" << endl;

    out << "struct " << SHADER_TYPE_NAME << "\n"
        << "{\n"
        << "  const char* code;\n"
        << "  const int   size;\n"
        << "\n"
        << "  " << SHADER_TYPE_NAME << "( const char* c, int s ) : code(c), size(s)\n"
        << "  {}\n"
        << "};\n" << endl;
}



void header_def_end( ostream& out, const char* DEF_TAG )
{
    out << "\n#endif /* " << DEF_TAG << " */\n" << endl;
}


void file_listing( ostream& out, vector<string*> names )
{
    out <<
        "//\n" <<
        "// Summary of all files used for generation of this header:\n" <<
        "//" << endl;

    for( auto file = names.begin(); file != names.end(); ++file )
    {
        out << "// " << **file << endl;
    }

    out << "//" << endl;
}







int main( int argc, char* argv[] )
{
    if( argc < 2 )
    {
        cerr
            << "Missing output filename.\n"
            << "Usage:\n"
            << "  " << argv[0] << "[output filename]" << endl;
        return 1;
    }

    string of_name = argv[1];

    string macro_name = "_";

    for( unsigned i = 0; i < of_name.length(); i++ )
    {
        if( 'a' <= of_name[i] && of_name[i] <= 'z' )
        {
            macro_name += of_name[i] - 0x20;
        }
        else if( 'A' <= of_name[i] && of_name[i] <= 'Z' )
        {
            macro_name += of_name[i];
        }
        else if( '0' <= of_name[i] && of_name[i] <= '9' )
        {
            macro_name += of_name[i];
        }
        else
        {
            macro_name += "_";
        }
    }
    macro_name += "_";


    DIR* directory = opendir( "./" );
    struct dirent* dir_dat;

    string filename;
    ifstream inf;

    ofstream of;
    of.open( of_name.c_str() );

    bool commented = false, begun = false;

    vector<string*> filenames;

    while( (dir_dat = readdir( directory )) )
    {
        filename = dir_dat->d_name;
        if( filename[0] != '.' ) // Ignore hidden files
        {
            //get file extension.
            size_t extension_start = filename.find_last_of( '.' );
            size_t type_start = filename.find_first_of( '.' );
            if( extension_start != std::string::npos )
            {
                string extension = filename.substr( extension_start );
                if( extension == ".glsl" )
                {
                    filenames.push_back( new string(filename) );

                    string shader_name = filename.substr( 0, type_start );
                    string shader_type = filename.substr(
                            type_start + 1,
                            extension_start - (type_start + 1));
                    if( !commented )
                    {
                        insert_comment( of, argv[0] );
                        commented = true;
                    }


                    if( !begun )
                    {
                        header_def_start( of, macro_name.c_str() );
                        begun = true;
                    }

                    for( int i = 0; shader_name[i] != 0; i++ )
                    {
                        if( shader_name[i] > 0x40 && shader_name[i] < 0x7B )
                            shader_name[i] -= 0x20;
                    }

                    inf.open( filename.c_str() );

                    if( !inf.good() )
                    {
                        cerr
                            << "Could not read file <" << filename 
                            << ">, skipping." << endl;
                        inf.close();
                        continue;
                    }

                    string shader_var_name = shader_name + "_" + shader_type;


                    of << "//\n// From file:  " << filename << "\n//" << endl;

                    string file_text = "";

                    string line;
                    string length;
                    for( getline( inf, line ); !inf.eof(); getline( inf, line ) )
                    {
                        if( line != "" )
                        {
                            file_text += DQ + line + "\\n" + DQ + "\n";
                            length += line + "\n";
                        }
                    }

                    of << "const " << SHADER_TYPE_NAME << " "
                        << shader_var_name << "(\n  ";
                    for( unsigned i = 0; i < file_text.length(); i++ )
                    {
                        of << file_text[i];
                        if( file_text[i] == '\n' )
                            of << "  ";
                    }
                    of << ",\n  " << length.length() << endl;
                    of << ");\n\n" << endl;

                    inf.close();
                }
            }
        }
    }

    if( commented || begun )
    {
        header_def_end( of, macro_name.c_str() );
        file_listing( of, filenames );
        of << endl << endl;
        of.close();

        filenames.clear();
    }
    else
    {
        cerr << "No files to process.\n" << endl;
        of << " ";
        of.close();
    }
    return 0;
}
