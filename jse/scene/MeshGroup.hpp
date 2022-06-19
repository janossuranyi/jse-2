#ifndef JSE_SCENE_MESHGROUP_H
#define JSE_SCENE_MESHGROUP_H

#include <vector>
#include "core/Types.hpp"
#include "scene/Mesh.hpp"

namespace jse::scene {

    class MeshGroup
    {
    public:
        core::String name;
        std::vector<Mesh> meshes;
    };
}
#endif