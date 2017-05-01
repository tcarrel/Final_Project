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
#include<ctime>


#ifndef  _RANDOM_H_



/** Encapsulates random number seeding.
 *  There is no need to create this outside of the any of the following
 * template functions, so it's ctor is declared as private with only
 * the template functions as friend functions being able to create the
 * object.
 */
class Random
{
    template<typename T>
        friend T get_rand( void );
    template<typename T>
        friend T get_rand( T );
    template<typename T>
        friend T get_rand( T, T );
    template<typename T, typename U>
        friend T get_rand( T, U );
    template<bool>
        friend bool get_rand( void );

    private:
    /** Seeds the random number generator only once.
    */
    Random( void )
    {
        if( !seeded )
        {
            seeded = true;
            srand( time( NULL ) );
        }
    }

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

    return static_cast<T>(rand()) / static_cast<T>(RAND_MAX);
}






/**
 *@param max the top end of the range to be returned.
 * @return Random number [0, max).
 */
template<typename T> T get_rand( T max )
{
    Random r;

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

    T num = static_cast<T>(rand());
    T den = static_cast<T>(RAND_MAX/(max - min));

    return min + (num/den);
}





/**
 * Specialization to return a randomized boolean.
 */
template<> bool get_rand( void )
{
    Random e;

    return rand() & 1;
}



#endif

