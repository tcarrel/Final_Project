/**
 *
 * \file random.h
 * \author random.cpp
 *
 * \brief Declares and defines template functions for random number generation.
 *
 */


#include<cstdint>
#include<cstdlib>

#include "random_seed.h"

#ifndef  _RANDOM_H_
# define _RANDOM_H_



/**
 * @return A random number [0,1].
 */
template<typename T> T get_rand( void )
{
    __Seed r;

    return static_cast<T>(rand()) / static_cast<T>(RAND_MAX);
}






/**
 *@param max the top end of the range to be returned.
 * @return __Seed number [0, max).
 */
template<typename T> T get_rand( T max )
{
    __Seed r;

    return static_cast<T>(rand()) / (static_cast<T>(RAND_MAX/max));
}





/**
 * @param min The minimum of the range.
 * @param max The maximum of the range.
 * @return __Seed number in the range [min,max].
 */
template<typename T> T get_rand( T min, T max )
{
    __Seed r;

    T num = static_cast<T>(rand());
    T den = static_cast<T>(RAND_MAX/(max - min));

    return min + (num/den);
}





/**
 * @param min The minimum of the range.
 * @param max The maximum of the range.
 * @return __Seed number in the range [min,max].
 */
template<typename T, typename U> T get_rand( T min, U max )
{
    __Seed r;

    T num = static_cast<T>(rand());
    T den = static_cast<T>(RAND_MAX/(max - min));

    return min + (num/den);
}





/**
 * Specialization to return a randomized boolean.
 */
/*
   template<> bool get_rand( void )
   {
   __Seed e;

   return rand() & 1;
   }
   */



#endif

