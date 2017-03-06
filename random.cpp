/**
 *
 * \file random.cpp
 * \author Thomas R. Carrel
 *
 * \brief Defines the random class's functions.  All functions are static, so
 * it is never necessary to instanciate a Random object.
 */



#include "random.h"


/** Tracks whether or not the random number generator has been seeded.
 */
bool Random::seeded = false;


/** Static function, returns a random number in the range [0, max).
 * \param max the top end of the range to be returned.
 */
uint32_t Random::rand_unsigned( uint32_t max )
{
    if( !seeded )
    {
        seeded = true;
        srand( time( NULL ) );
    }

    return rand() % max;
}
