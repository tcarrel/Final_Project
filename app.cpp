

#include"app.h"


Application::Application( void ) :
    window_( new Window ),
    programs_( new Shader*[4] ),
    prog_qty_( 0 ),
    prog_qty_max_( 4 )
{

    start_up();

    if( window_->good() )
        cerr << "Window created successfully.";
    else
        cerr << "Failed to create window.";
    cerr << endl;
}



void Application::start_up( void )
{
    load_shader();
    for( unsigned i = 0; i < prog_qty_; i++ )
        programs_[i]->compile();

    SDL_Init( SDLSYSTEMS );
    window_->init();
}



int Application::run( void )
{

//    if( load_shader() )
        SDL_Delay(3000);

    return 0;
}


bool Application::load_shader( )
{
    if( prog_qty_ >= prog_qty_max_ )
        add_shader_slots( 4 );

    ++prog_qty_;

    programs_[0] = new Shader;
    return
        programs_[0]->load_vertex_shader("vertex") &&
        programs_[0]->load_fragment_shader("fragment");
}



void Application::add_shader_slots( unsigned qty = 0 )
{
    unsigned new_qty = prog_qty_max_ + ((qty == 0) ? prog_qty_max_ : qty );

    Shader** old = programs_;

    programs_ = new Shader*[new_qty];

    for( unsigned i = 0; i < prog_qty_; i++ )
    {
        programs_[i] = old[i];
        old[i] = NULL;
    }
    prog_qty_max_ = new_qty;
    delete [] old;
}



Application::~Application( void )
{
    SDL_Quit();
}

