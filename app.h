

#ifndef  APPLICATION_H
# define APPLICATION_H

#include"constants.h"
#include"window.h"
#include"shader_program.h"


#include<stdio.h>


class Application
{
    public:
        Application( void );
        ~Application(void );

       int run( void ); 
    private:

       void start_up( void );

       Window*  window_;
};

#endif
