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
    /** Redraw window.
     */
    class Window_Redraw : public Command
    {
        public:
            /** Ctor
             * \param w The window that program is running in.
             */
            Window_Redraw( App::Window* w ) : w_(w) {}

            /** Dtor.
             */
            ~Window_Redraw( void ) { w_ = NULL; }

            /** Redraws the window after it has been minimized.
             */
            void execute( void )
            {
                w_->redraw();
            }

        private:
            App::Window* w_;
    };

} // Input namespace.
