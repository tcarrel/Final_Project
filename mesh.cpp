/**
 * \file mesh.cpp
 * \author Thomas R. Carrel
 *
 * \brief Definitions for Mesh class.
 */


#include "mesh.h"

#include "shader_program.h"


Mesh::Mesh( void ) : verts_sent_to_gpu_( false ), ipv_( 3 )
{
    /** Hard coded cube mesh
     * Delete later.
     * vertex coordinates borrowed from
* http://www.opengl-tutorial.org/beginners-tutorials/tutorial-4-a-colored-cube/
     */
    vertices_ = new Vertex[ 36 ]
    {
        { -1.0f,-1.0f,-1.0f }, { -1.0f,-1.0f, 1.0f }, { -1.0f, 1.0f, 1.0f },
            { 1.0f, 1.0f,-1.0f }, { -1.0f,-1.0f,-1.0f }, { -1.0f, 1.0f,-1.0f },
            { 1.0f,-1.0f, 1.0f }, { -1.0f,-1.0f,-1.0f }, { 1.0f,-1.0f,-1.0f },
            { 1.0f, 1.0f,-1.0f }, { 1.0f,-1.0f,-1.0f }, { -1.0f,-1.0f,-1.0f },
            { -1.0f,-1.0f,-1.0f }, { -1.0f, 1.0f, 1.0f }, { -1.0f, 1.0f,-1.0f },
            { 1.0f,-1.0f, 1.0f }, { -1.0f,-1.0f, 1.0f }, { -1.0f,-1.0f,-1.0f },
            { -1.0f, 1.0f, 1.0f }, { -1.0f,-1.0f, 1.0f }, { 1.0f,-1.0f, 1.0f },
            { 1.0f, 1.0f, 1.0f }, { 1.0f,-1.0f,-1.0f }, { 1.0f, 1.0f,-1.0f },
            { 1.0f,-1.0f,-1.0f }, { 1.0f, 1.0f, 1.0f }, { 1.0f,-1.0f, 1.0f },
            { 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f,-1.0f }, { -1.0f, 1.0f,-1.0f },
            { 1.0f, 1.0f, 1.0f }, { -1.0f, 1.0f,-1.0f }, { -1.0f, 1.0f, 1.0f },
            { 1.0f, 1.0f, 1.0f }, { -1.0f, 1.0f, 1.0f }, { 1.0f,-1.0f, 1.0 },
    };
    qty_ = 36;
}





/** Load vertex data from .obj file.
 * \param filename The name of the .obj file to load.
 * \todo this cannot be implented until the recursive descent parser for
 * loading .obj's has been writen.
 */
Mesh::Mesh( GLchar* filename ) : Mesh()
{
    /// Call the .obj loader, etc.
}





/** Get hard-coded vertices.
 * \param verts And array of vertices.
 * \param count the number of vertices.
 */
Mesh::Mesh( Vertex* verts, GLuint count ) :
    Mesh()//, vertices_( verts ), qty_( count )
{
    vertices_   = verts;
    qty_        = count;
}







/** Mesh dtor.
*/
Mesh::~Mesh( void )
{
    if( vertices_ )
        delete [] vertices_;

    /**
     * We cannot delete shaders explicitly as there is no way to easily tell if
     * they are be used in for rendering multiple meshes.  For the time being,
     * we will rely on the OS to clean up after us after program exit.  As the
     * program becomes more mature, we will store a list of all shader program
     * created and create a SIGKILL handler to delete them on exit and no
     * sooner.
     */
    shader_ = NULL;
}






/** For now, this will be responsible for sending all the draw calls to the gpu.
 * Later, this will be responsible only for creating command packets and
 * sending those to the command buffer.
 * \param prog If using a shader other than the 
 */
void Mesh::draw( Shader* prog )
{
    if( prog )
    {
        prog->use_program();
    }
    else
    {
        shader_->use_program();
    }

}




//void Mesh::





/**  Set the default shader program to be used when rendering this mesh.
 * \param p A pointer to the Shader object that will be used.
 */
void Mesh::set_shader( Shader* p )
{
    shader_ = p;
}
