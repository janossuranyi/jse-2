#ifndef JSE_SCENE_H
#define JSE_SCENE_H

#include <vector>
#include "core/Types.hpp"
#include "scene/Mesh.hpp"
#include "scene/Node.hpp"
#include "graphics/Material.hpp"
#include "graphics/Image.hpp"
#include "graphics/Camera.hpp"
#include "graphics/Light.hpp"

namespace jse::scene {

	class Scene
	{
	public:
		bool LoadFromGltf(const core::String& filename);
	public:
		Scene(const core::String& name_) :name(name_) {}
		core::String name;
		std::vector<Mesh> meshes;
		std::vector<Node> nodes;
		std::vector<graphics::Image> images;
		std::vector<graphics::Material> materials;
		std::vector<graphics::Camera> cameras;
		std::vector<graphics::Light> lights;
	};
}
#endif // !JSE_SCENE_H
