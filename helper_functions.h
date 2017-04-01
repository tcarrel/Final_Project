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


extern  glm::vec4       to_vec_color( uint32_t );
extern  std::string     numtoa( const uint32_t& i );
extern  void            skip_whitespace( std::ifstream& );
extern  std::string     bold( const std::string& );
extern  SHADER_TYPE_NAME* get_shdr( const std::string& );

