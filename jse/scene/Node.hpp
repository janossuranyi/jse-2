#ifndef JSE_SCENE_NODE_H
#define JSE_SCENE_NODE_H

#include <vector>
#include <string>
#include "core/Types.hpp"
#include "core/math/Matrix.hpp"

namespace jse {

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

		Node() : type(nodeType_t::NT_UNKNOWN), name(""), parent(-1), object(-1), transformUpdated(false) {}
		Node(nodeType_t type, const std::string& name, int parent, int object);

		nodeType_t type;
		std::string name;
		int parent;
		int object;

		std::vector<int> children;
		std::vector<float> weights;
		mat4 modelTransform{ 1.0f };
		mat4 worldTransform{ 1.0f };

		vec3 position{ 0.0f };
		vec3 scale{ 1.0f };
		quat rotation{ 1.0f,0.0f,0.0f,0.0f };

		bool transformUpdated;
	};

}
#endif // !JSE_SCENE_NODE_H
