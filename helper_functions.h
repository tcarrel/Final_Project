/*
 * \file helper_functions.h
 * \author Thomas R. Carrel
 *
 * \brief Declares some useful helper functions.
 *
 */

#include<fstream>
#include<string>

#include "shaders.h"



//Data manipulation.
#ifdef GLM_INCLUDED
 extern         glm::vec4           to_vec_color( uint32_t );
#endif

extern          std::string         numtoa( const uint32_t& );
extern          void                skip_whitespace( std::istream& );

//Other
extern          SHADER_TYPE_NAME*   get_shdr( const std::string& );
extern          std::string         shader_filename_to_struct_name(
        const std::string& );





//Text formatting


#ifndef  __TEXT_FORMATTING_HELPER_FUNCTIONS__
# define __TEXT_FORMATTING_HELPER_FUNCTIONS__
// These are defined here so they can be inlined.

/**  Return the provided text in bright red.
 * @param text The text to be changed.
 */
inline std::string bright_red( const std::string& text )
{
    return "\033[1;31m" + text + "\033[0m";
}




/**  Return the provided text in red.
 * @param text The text to be changed.
 */
inline std::string red( const std::string& text )
{
    return "\033[0;31m" + text + "\033[0m";
}




/**  Return the provided text in bold.
 * @param text The text to be changed.
 */
inline std::string bold( const std::string& text )
{
    return "\033[1m" + text + "\033[0m";
}
#endif /*__TEXT_FORMATTING_HELPER_FUNCTIONS__*/
