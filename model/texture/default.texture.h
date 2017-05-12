



#include "texture_base.h"




#ifndef   _DEFAULT_TEXTURE_H_
# define  _DEFAULT_TEXTURE_H_

# include<string>
using std::string;

struct String_Color_Pair
{
    string      str;
    GLuint      color;
};

namespace Model
{
    namespace Texture
    {
        class  Texture_Default : public Texture_base
        {
            public:
                Texture_Default( void );
                ~Texture_Default( void );

            private:
                Texture_Default( const String_Color_Pair& );

                GLuint      color_;
        };
    } //Texture namespace.
} //Model namespace.

#endif /* _DEFAULT_TEXTURE_H_ */
