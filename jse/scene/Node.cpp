#include "Node.hpp"

namespace jse::scene {

	Node::Node(nodeType_t type, const core::String& name, int parent, int object)
	{
		this->type = type;
		this->name = name;
		this->parent = parent;
		this->object = object;
	}
}
