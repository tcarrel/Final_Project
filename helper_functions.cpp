

#include "helper_functions.h"


glm::vec4 to_vec_color( int32_t color )
{
    /*
    union {
        char    rgba[4];
        int32_t color;
    } Convert;

    Convert.color = color;

    float rgba[4];

    for( char i = 0; i < 4; i++ )
    {
        rgba[i] = (Convert.rgba[i]) / 256.0f;
    }
    */

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
