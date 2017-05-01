/**
 *
 * @file function_timer.h
 * @author Thomas R. Carrel
 *
 * @brief A timer to provide some basic function-level profiling.
 *
 */






#ifndef  _FUNCTION_TIMER_H_
# define _FUNCTION_TIMER_H_

#include <cstdio>
#include <string>
#include <chrono>


/** 
 * Provides some very basic function-level profiling.
 * Creating an object at beginning of a function will result in the duration
 * that the function ran being output when the object is destroyed as a result
 * of the function going out of scope.  It can also be used to time a single
 * pass through a loop or any other portion of code that has its own scope.
 * Creating the object globally, for example, will time the overall runtime of
 * the program or including one as the member of a class will end up outputing
 * a lifetime for that object.  It should not be created as a pointer.
 */
class Function_Timer
{
    public:
        Function_Timer( const std::string&, FILE* );
        ~Function_Timer( void );

    private:
        /** File pointer for output.
         */
        FILE*                                               print_to_;
        /** The message to be be prepended when the time is output.
         */
        std::string                                         message_;
        /** The start time.
         */
        std::chrono::high_resolution_clock::time_point      start_;
};


#endif /* _FUNCTION_TIMER_H_ */
