/**
 * \file constants.h
 * \author Thomas R. Carrel
 *
 * \brief Provides a single location for the definition of all global
 * constants, enums, and macros.
 */


#ifndef CONSTANTS_H
# define CONSTANTS_H

#include<GL/glew.h>

# include<cassert>

# include<string>
using std::string;

# include "colors.h"

/**
 * The SDL sub-systems to be initialized.
 */

#define SDLSYSTEMS (SDL_INIT_VIDEO | SDL_INIT_EVENTS | \
        SDL_INIT_JOYSTICK | SDL_INIT_GAMECONTROLLER | \
        SDL_INIT_TIMER )

#define q(x) #x
# define xxx( x ) q( x )
//#define xxx( x ) qq( x )

#  ifdef COMPILER_ID_STRING
const string COMPILER           =   xxx(COMPILER_ID_STRING);
#  endif

#  ifdef OS_ID_STRING
const string OPERATING_SYSTEM   =   xxx(OS_ID_STRING);
#  endif

#  ifdef AUTHOR_ID_STRING
const string AUTHOR             =   xxx(AUTHOR_ID_STRING);
#  endif

#  ifdef COMPILE_TIME
const string COMPILE_TIME_AND_DATE = xxx(COMPILE_TIME);
#  endif

# undef xxx
#undef q

const string    TITLE   =   "Senior Project"; ///< The name of the game.
                                              ///< Mainly used by the windowing
                                              ///< system.
const bool      ERROR   =   false; ///< For error checking, so that fuctions
                                   ///< returning errors can be consistant.

/** Shader types.  Used in compiling shaders.
 */
enum Shaders
{
    VERTEX_SHADER = GL_VERTEX_SHADER,
    TCS_SHADER = GL_TESS_CONTROL_SHADER,
    TESSELATION_CONTROL_SHADER = TCS_SHADER,
    TEV_SHADER = GL_TESS_EVALUATION_SHADER,
    TESSELATION_EVALUATION_SHADER = TEV_SHADER,
    GEOMETRY_SHADER = GL_GEOMETRY_SHADER,
    FRAGMENT_SHADER = GL_FRAGMENT_SHADER,
    COMPUTE_SHADER = GL_COMPUTE_SHADER
};



/** Used for setting up the Scene_Graph.
 */
# define PERSPECTIVE true
/** Used for setting up the Scene_Graph.
 */
# define ORTHOGRAPHIC false

#endif
