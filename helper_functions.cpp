/**
 * \file helper_functions.cpp
 * \author Thomas R. Carrel
 * 
 * \brief Defines some useful helper functions.
 */

#include<string>
#include<sstream>
#include<glm/glm.hpp>

/**
 *  Converts a hex integer to a vec4 color.
 *  \param color The hex value of the desired color, RGBA-format, 8-bits per
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
 * \param i The integer.
 */
std::string numtoa( uint32_t i )
{
    std::stringstream S;
    S << i;
    return S.str();
}

