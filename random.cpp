



#include "random.h"


bool Random::seeded = false;

uint32_t Random::rand_unsigned( uint32_t max )
{
    if( !seeded )
    {
        seeded = true;
        srand( time( NULL ) );
    }
    return rand() % max;
}
