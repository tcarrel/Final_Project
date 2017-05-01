/**
 *
 * @file function_timer.cpp
 * @author Thomas R. Carrel
 *
 * @brief Defines the Function_Timer class.
 *
 */



#include "function_timer.h"




/** Ctor.
 * @param f The function name, used in the output when the destructor is
 * called, the timer is started after the string is copied so that its affect
 * on a function's runtime is minimal.
 * @param file The file or stream to output to.
 */
Function_Timer::Function_Timer( const std::string& f, FILE* file ) :
    print_to_( file ),
    message_(f),
    start_( std::chrono::high_resolution_clock::now() )
{}

/** Dtor.
 * Calculates the time elapsed since the object was created and outputs the
 * time to stderr.
 */
Function_Timer::~Function_Timer( void )
{
    std::chrono::duration<long double> time =
        std::chrono::duration_cast<std::chrono::nanoseconds>(
                std::chrono::high_resolution_clock::now() - start_ );

    fprintf(
            print_to_,
            "%s took %.15Lf seconds.\n",
            message_.c_str(),
            time.count() );
}
