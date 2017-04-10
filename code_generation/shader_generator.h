/*
 *
 * @file shader_generator.h
 * @author Thomas R. Carrel
 *
 * @brief Automatically generating shader code based on object models is
 * preferable to using manually programmed shaders.  Unfortunately, I cannot
 * write the routine for shader generation in the time I have remaining.  I'll
 * have to put this off until after graduation.
 *
 */

#include "gen_flags_enum.h"

#ifndef  _SHADER_GENERATOR_H_
#define _SHADER_GENERATOR_H_


class Shader;

namespace Shader_Gen
{
    class Shader_Generator
    {
        public:
        Shader_Generator(  void );
        ~Shader_Generator( void );

        Shader* operator()(
                Ver_gen_enum,
                TCS_gen_enum,
                TEV_gen_enum,
                Geo_gen_enum,
                Fra_gen_enum,
                Com_gen_enum );
        private:
    };
} //Shader_Gen namespace.

/*_SHADER_GENERATOR_H_*/
#endif

