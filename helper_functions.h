/*
 * \file helper_functions.h
 * \author Thomas R. Carrel
 *
 * \brief Declares some useful helper functions.
 *
 */

#include<fstream>
using std::istream;

#include<string>
using std::string;

#include "shaders.h"



//Data manipulation.
#ifdef GLM_INCLUDED
 extern         glm::vec4           to_vec_color( uint32_t );
#endif

extern          string         numtoa( const uint32_t& );
extern          void                skip_whitespace( istream& );

//Other
extern          SHADER_TYPE_NAME*   get_shdr( const string& );
extern          string         shader_filename_to_struct_name( const string& );

//extern          int                 get_bits( const float& );

extern          void  check_SOIL_error( unsigned char*,    const string& );


extern          float get_refractive_index( const string& );
extern          float get_refraction_ratio( const string&, const string& );



//Text formatting


#ifndef  __TEXT_FORMATTING_HELPER_FUNCTIONS__
# define __TEXT_FORMATTING_HELPER_FUNCTIONS__
// These are defined here so they can be used inline linkage.

/**  Return the provided text in bright red.
 * @param text The text to be changed.
 */
inline string bright_red( const string& text )
{
    return "\033[1;31m" + text + "\033[0m";
}




/**  Return the provided text in red.
 * @param text The text to be changed.
 */
inline string red( const string& text )
{
    return "\033[0;31m" + text + "\033[0m";
}



/**  Return the provided text in bright green.
 * @param text The text to be changed.
 */
inline string bright_green( const string& text )
{
    return "\033[1;32m" + text + "\033[0m";
}



/**  Return the provided text in green.
 * @param text The text to be changed.
 */
inline string green( const string& text )
{
    return "\033[0;32m" + text + "\033[0m";
}



/**  Return the provided text in bright cyan.
 * @param text The text to be changed.
 */
inline string bright_cyan( const string& text )
{
    return "\033[1;36m" + text + "\033[0m";
}



/**  Return the provided text in cyan.
 * @param text The text to be changed.
 */
inline string cyan( const string& text )
{
    return "\033[0;36m" + text + "\033[0m";
}





/**  Return the provided text in bold.
 * @param text The text to be changed.
 */
inline string bold( const string& text )
{
    return "\033[1m" + text + "\033[0m";
}
#endif /*__TEXT_FORMATTING_HELPER_FUNCTIONS__*/
