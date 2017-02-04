/**
 * Define/set global constants.
 *
 * \file constants.h
 * \author Thomas R. Carrel
 */


#ifndef CONSTANTS_H
# define CONSTANTS_H

# include<string>
using std::string;

#define SDLSYSTEMS SDL_INIT_VIDEO

const string    TITLE   =   "Senior Project"; ///< The name of the game.
                                              ///< Mainly used by the windowing
                                              ///< system.
const bool      ERROR   =   false; ///< For error checking, so that fuctions
                                   ///< returning errors can be consistant.

/** Shader types.  Used in compiling shaders.
 */
enum Shaders {
    VERTEX_SHADER,
    TCS_SHADER,
    TESSELATION_CONTROL_SHADER = TCS_SHADER,
    TEV_SHADER,
    TESSELATION_EVALUATION_SHADER = TEV_SHADER,
    GEOMETRY_SHADER,
    FRAGMENT_SHADER,
    COMPUTE_SHADER
};

#endif
