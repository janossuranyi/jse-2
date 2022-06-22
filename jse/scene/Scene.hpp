#ifndef JSE_SCENE_H
#define JSE_SCENE_H

#include <vector>
#include "core/Types.hpp"
#include "scene/MeshGroup.hpp"
#include "scene/Node.hpp"
#include "graphics/Material.hpp"
#include "graphics/Image.hpp"
#include "graphics/Camera.hpp"
#include "graphics/Light.hpp"

namespace jse {

	class Scene
	{
	public:
		bool LoadFromGltf(const std::string& filename);
	public:
		Scene(const std::string& name_) :name(name_) {}
		std::string name;
		std::vector<MeshGroup> meshes;
		std::vector<Node> nodes;
		std::vector<Image> images;
		std::vector<Material> materials;
		std::vector<Camera> cameras;
		std::vector<Light> lights;
	};
}
#endif // !JSE_SCENE_H
