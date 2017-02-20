




#include<glm/glm.hpp>


#ifndef  _SCENE_GRAPH_H_
# define _SCENE_GRAPH_H


namespace Model
{

    class Model;


    /**
     * The scene graph.  For render the "world."
     */
    class Scene_Graph_Root
    {
        public:
            Scene_Graph( void );

        private:

            Model* root_;
            glm::mat4 camera_;
    };

} //Model namespace.

#endif
