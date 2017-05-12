






#include<cstdlib>
#include<ctime>


#ifndef  _RANDOM_SEEDER_H_
# define _RANDOM_SEEDER_H_


/** Encapsulates random number seeding.
 *  There is no need to create this outside of the any of the following
 * template functions, so it's ctor is declared as private with only
 * the template functions as friend functions being able to create the
 * object.
 */
class __Seed
{
    public:
        /** Seeds the random number generator only once.
        */
        __Seed( void )
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


#endif /*  _RANDOM_SEEDER_H_ */
