#ifndef JSE_SCENE_MESHGROUP_H
#define JSE_SCENE_MESHGROUP_H

#include <vector>
#include "scene/Mesh.hpp"

namespace jse::scene {

    class MeshGroup
    {
    public:
        std::vector<Mesh> meshes;
    };
}
#endif