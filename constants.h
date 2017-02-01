
#ifndef CONSTANTS_H
# define CONSTANTS_H

# include<string>
using std::string;

#define SDLSYSTEMS SDL_INIT_VIDEO

const string    TITLE   =   "Galaxy 5000X";
const bool      ERROR   =   false;

enum Shaders {
    VERTEX_SHADER,
    TCS_SHADER,
    TEV_SHADER,
    TESSELATION_EVALUATION_SHADER = TEV_SHADER,
    GEOMETRY_SHADER,
    FRAGMENT_SHADER,
    COMPUTE_SHADER
};

#endif
