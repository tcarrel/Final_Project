/**
 *
 * \file random.h
 * \author random.cpp
 *
 * \brief A wrapper for random numbers.
 *
 */


#include<cstdint>
#include<cstdlib>
#include<ctime>


#ifndef  _RANDOM_H_
# define _RANDOM_H_

/** Encapsulates random number generation.
 */
class Random
{
    public:
        static uint32_t rand_unsigned( uint32_t );
    private:
        static bool seeded;
};

#endif
