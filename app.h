

#ifndef  APPLICATION_H
# define APPLICATION_H

#include"constants.h"
#include"window.h"
#include"shader_program.h"

class Application
{
    public:
        Application( void );
        ~Application(void );

       int run( void ); 
    private:

       void start_up( void );

       Window*  window_;

       Shader** programs_;

       unsigned prog_qty_;
       unsigned prog_qty_max_;
       void     add_shader_slots( unsigned );
       bool     load_shader();
};

#endif
