/**
 * 
 * \file obj.h
 * \author Thomas R. Carrel
 */


#ifndef  _OBJ_LOADER_H_
# define _OBJ_LOADER_H_

//  This class should only be getting used during loading so its speed is not
// absolutely critical, so stl containers are sufficient.
# include<iostream>
using std::string;
# include<fstream>
# include<vector>
using std::vector;
# include<map>
using std::map;


# include<glm/glm.hpp>

# include "../model.h"
# include "OBJ_except.h"


template<typename> class Tracking_List;
class Shader;

namespace Model
{
    class Model;
    class Mesh;
    class Vertex_Array;
    class Vertex;

    namespace OBJ
    {
        class Model_list;
        class OBJ_Exception;

        /** This class takes a wavefront .obj file and loads it into a
         * Vertex_Array object.
         */
        class OBJ_File
        {
            public:
                OBJ_File( void );
                ~OBJ_File( void );

                Mesh* load_file(
                        const string&,
                        Shader*,
                        bool,
                        GLfloat ) throw(  OBJ_Exception );

                void        reset( void );
                void        trace( const string& );
                void        stop_trace( void );
                glm::vec3   size(  void );
                float       max_dim(   void );

            private:

                //Private functions.///////////////////////

                void        parse( void ) throw(  OBJ_Exception );
                void        close( void );

                /**  Opens an .obj file.
                 * \param f The filename.
                 */
                inline void open( const char* f )
                { filename_ = new string( f ); file_ = new std::ifstream( f ); }

                /**  Opens an .obj file.
                 * \param s The filename.
                 */
                inline void open( const string& s )
                { open( s.c_str() ); }

                /**  Condition of the input file stream.
                 */
                inline bool good( void )
                { return file_->good(); }

                /**  Checks whether or not a file is opened.
                 */
                inline bool is_open( void )
                { return file_->is_open(); }

                /**  Checks if eof has been read.
                 */
                inline bool eof( void )
                { return file_->eof(); }

                void add_mesh();
//                void fill( GLuint, bool );

                void vertex( std::istream& );
                void tex_coord( std::istream& );
                void normal( std::istream& );
                void v( std::istream& );
                void g_or_o( std::istream& );
                void f( std::istream& );
                void m( std::istream& );
                void s( std::istream& );
                void u( std::istream& );
                void comment( std::istream& );
                void measure( const float&, const float&, const float& );

                /**  Returns the next character to be read from the file
                 * without popping it from the queue.
                 */
                inline char peek( void ) { return file_->peek(); }


                //Internal types.//////////////////////////
                struct Index_Set
                {
                    int v = 0;
                    int t = 0;
                    int n = 0;
                };

                struct Range{
                    string      name;
                    unsigned    start;
                    unsigned    end;
                };


                //Private members./////////////////////////
                std::ifstream*  file_; ///< IF stream.
                std::ofstream*  trace_; ///< OF stream for debug tracing.

                vector<glm::vec3> vertices_;
                vector<glm::vec2> textures_;
                vector<glm::vec3> normals_;

                vector<Index_Set*> faces_;

                string*     filename_; ///< The name of the file being read,
                                       ///< mostly for debugging purposes.
                string*     obj_name_; ///< The name of the object.

                unsigned    line_; ///< The previous line number;

                GLfloat     size_[3]; 
                GLfloat*    min_;
                GLfloat*    max_;

                Mesh*       top_mesh_;
                GLuint      mesh_qty_;
                Vertex_Array*
                            cur_va_;

                Tracking_List<Mesh> m_list_;
//                Model_list  m_list_;

                bool        color_by_;
                bool        already_loaded_;
                bool        loading_;
        };

    } // OBJ namespace.

} // Model namespace.

#endif
