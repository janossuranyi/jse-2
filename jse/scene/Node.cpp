#include "Node.hpp"

namespace jse {

	Node::Node(nodeType_t type, const std::string& name, int parent, int object)
	{
		this->type = type;
		this->name = name;
		this->parent = parent;
		this->object = object;
	}
}
