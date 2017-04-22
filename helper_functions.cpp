/**
 * \file helper_functions.cpp
 * \author Thomas R. Carrel
 * 
 * \brief Defines some useful helper functions.
 */

#include<string>
#include<sstream>
using std::stringstream;
#include<fstream>
#include<cctype>
#include<glm/glm.hpp>

#include<SOIL/SOIL.h>

#include "helper_functions.h"

/**
 *  Converts a hex integer to a vec4 color.
 *  @param color The hex value of the desired color, RGBA-format, 8-bits per
 *  field.
 */
glm::vec4 to_vec_color( uint32_t color )
{
    float rgba[4];

    rgba[0] = (float) ((color & 0xFF000000 ) >> 24 );
    rgba[1] = (float) ((color & 0x00FF0000 ) >> 16 );
    rgba[2] = (float) ((color & 0x0000FF00 ) >> 8 );
    rgba[3] = (float) (color & 0x000000FF );

    return glm::vec4(
        rgba[0] / 255.0f,
        rgba[1] / 255.0f,
        rgba[2] / 255.0f,
        rgba[3] / 255.0f );
}




/**  Converts and integer to a string.
 * @param i The integer.
 */
string numtoa( const uint32_t& i )
{
    stringstream S;
    S << i;
    return S.str();
}






/**  Skip whitespace at the beginning of a stream.
 * @param in The stream to remove whitespace from.
 */
void skip_whitespace( istream& in )
{
    while( isspace( in.peek() ) )
    {
        in.ignore();
    }
}















/**  Converts a shader program filename to an internal shader name.
 * @param fname The filename.
 * @return The internally used shader name.
 */
string shader_filename_to_struct_name( const string& fname )
{
    string name = fname.substr( 0, fname.find_first_of('.') ) + "_";

    for( unsigned i = 0; i < name.length(); i++ )
    {
        if( 'a' <= name[i] && name[i] <= 'z' )
        {
            name[i] -= ('a' - 'A');
        }
    }
    name += fname.substr( fname.find_first_of('.') )[1];

    return name;
}




/**  Get the raw binary data from a float in a type that can be used with
 * bitwise operations.
 * @param f The float to be copied.
 * @return An unsigned int that has the same binary representation as the
 * float that had been passed in.
 */
/*
inline unsigned get_bits( const float& f )
{
    return *((int*) &f);
}
*/






/**  Check an image for errors from the SOIL library.
 * @param image The raw image data.
 * @param file The filename of the image.
 */
void check_SOIL_error( unsigned char* image, const string& file )
{
    if( image )
    {
        return;
    }

    fprintf(
            stderr,
            "Image Load Error < %s > %s\n",
            file.c_str(),
            SOIL_last_result()
           );
}






/** Get the refractive index (n) of common materials.
 * @param material The name of the material being requested.  No error
 * checking is done, so this should be all caps.
 * @return The refractive index of the material.
 */
float get_refractive_index( const string& material )
{
    if( material == "AIR" )
    {
        return 1.0f;
    }

    if( material == "WATER" )
    {
        return 1.33f;
    }

    if( material == "ICE" )
    {
        return 1.309f;
    }

    if( material == "GLASS" )
    {
        return 1.52f;
    }

    if( material == "DIAMOND" )
    {
        return 2.42f;
    }

    return 1.00f;
}




/** Get the ratio of refractivity.
 * @param from The name of the material the object is meant to be 'submerged'
 * in.
 * @param to The name of the material the object is meant to be made of.
 * @return from/to
 */
float get_refraction_ratio( const string& from, const string& to )
{
    return get_refractive_index( from ) / get_refractive_index( to );
}
