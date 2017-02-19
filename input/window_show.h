/**
 * \file window_show.h
 * \author Thomas R. Carrel
 *
 * \brief React some events related to the window.
 */



#include "command.h"
#include "../app/window.h"

namespace Input
{
    //Redraw window.
    class Window_Redraw : public Command
    {
        public:
            Window_Redraw( App::Window* w ) : w_(w) {}
            ~Window_Redraw( void ) { w_ = NULL; }

            void execute( void )
            {
                w_->redraw();
            }

        private:
            App::Window* w_;
    };

} // Input namespace.
