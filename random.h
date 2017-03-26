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
        /** Seeds the random number generator only once.
        */
        void seed( void )
        {
            if( !seeded )
            {
                seeded = true;
                srand( time( NULL ) );
            }
        }
    private:
        static bool seeded;
};



/** Tracks whether or not the random number generator has been seeded.
 */
bool Random::seeded = false;





/**
 * @return A random number [0,1].
 */
template<typename T> T get_rand( void )
{
    Random r;
    r.seed();

    return static_cast<T>(rand()) / static_cast<T>(RAND_MAX);
}






/**
 *@param max the top end of the range to be returned.
 * @return Random number [0, max).
 */
template<typename T> T get_rand( T max )
{
    Random r;
    r.seed();

    return static_cast<T>(rand()) / (static_cast<T>(RAND_MAX/max));
}





/**
 * @param min The minimum of the range.
 * @param max The maximum of the range.
 * @return Random number in the range [min,max].
 */
template<typename T> T get_rand( T min, T max )
{
    Random r;
    r.seed();
    T num = static_cast<T>(rand());
    T den = static_cast<T>(RAND_MAX/(max - min));

    return min + (num/den);
}



/**
 * @param min The minimum of the range.
 * @param max The maximum of the range.
 * @return Random number in the range [min,max].
 */
template<typename T, typename U> T get_rand( T min, U max )
{
    Random r;
    r.seed();
    T num = static_cast<T>(rand());
    T den = static_cast<T>(RAND_MAX/(max - min));

    return min + (num/den);
}
#endif
