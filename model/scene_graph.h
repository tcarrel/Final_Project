






#ifndef  _SCENE_GRAPH_H_
# define _SCENE_GRAPH_H


namespace Model
{

    class Model;


    /**
     * The scene graph.  For render the "world."
     */
    class Scene_Graph
    {
        public:

        private:
            Model* world_; ///< The root of the scene graph.
    };

} //Model namespace.

#endif
