
#include "scene/Mesh.hpp"

#include <cassert>
namespace jse::scene {

	using namespace core::math;

	Mesh::Mesh()
	{		
	}

	Mesh::~Mesh()
	{
	}

	void Mesh::AllocPositions(unsigned numPos, unsigned numIndices, const primitiveType_t type)
	{
		if (numPrimitives > 0) return;

		xyz.resize(numPos);
		indices.resize(numIndices);

		this->type = type;
		this->numPrimitives = numPos;
		this->numIndices = numIndices;
	}

	void Mesh::AllocColors()
	{
		colors.resize(numPrimitives);
	}
	void Mesh::AllocNormals()
	{
		normals.resize(numPrimitives);
	}
	void Mesh::AllocTexCoords()
	{
		st.resize(numPrimitives);
	}
	void Mesh::AllocTangents()
	{
		tangents.resize(numPrimitives);
	}

}