#ifndef JSE_SCENE_NODE_H
#define JSE_SCENE_NODE_H

#include <vector>
#include "core/Types.hpp"
#include "core/math/Matrix.hpp";

namespace jse::scene {

	enum class nodeType_t
	{
		NT_CAMERA,
		NT_MESH,
		NT_LIGHT,
		NT_SKIN,
		NT_UNKNOWN
	};

	class Node
	{
	public:

		Node() : type(nodeType_t::NT_UNKNOWN), name(""), parent(-1), object(-1) {}
		Node(nodeType_t type, const core::String& name, int parent, int object);
		nodeType_t type;
		core::String name;		
		int parent;
		int object;

		std::vector<int> children;
		std::vector<float> weights;
		core::math::mat4 modelTransform{ 1.0f };
		core::math::mat4 worldTransform{ 1.0f };
	};

}
#endif // !JSE_SCENE_NODE_H
