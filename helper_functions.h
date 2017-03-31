/*
 * \file helper_functions.h
 * \author Thomas R. Carrel
 *
 * \brief Declares some useful helper functions.
 *
 */

#include<fstream>
#include<string>



extern  glm::vec4       to_vec_color( uint32_t );
extern  std::string     numtoa( GLuint i );
extern  void            skip_whitespace( std::ifstream& in );
extern  std::string     bold( const std::string& );
