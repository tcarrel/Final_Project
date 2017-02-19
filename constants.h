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

# include<string>
using std::string;

/**
 * The SDL sub-systems to be initialized.
 */

#define SDLSYSTEMS (SDL_INIT_VIDEO | SDL_INIT_EVENTS | \
        SDL_INIT_JOYSTICK | SDL_INIT_GAMECONTROLLER | \
        SDL_INIT_TIMER )


const string    TITLE   =   "Senior Project"; ///< The name of the game.
                                              ///< Mainly used by the windowing
                                              ///< system.
const bool      ERROR   =   false; ///< For error checking, so that fuctions
                                   ///< returning errors can be consistant.

/** Shader types.  Used in compiling shaders.
 */
enum Shaders {
    VERTEX_SHADER = GL_VERTEX_SHADER,
    TCS_SHADER = GL_TESS_CONTROL_SHADER,
    TESSELATION_CONTROL_SHADER = TCS_SHADER,
    TEV_SHADER = GL_TESS_EVALUATION_SHADER,
    TESSELATION_EVALUATION_SHADER = TEV_SHADER,
    GEOMETRY_SHADER = GL_GEOMETRY_SHADER,
    FRAGMENT_SHADER = GL_FRAGMENT_SHADER,
    COMPUTE_SHADER = GL_COMPUTE_SHADER
};

#endif
