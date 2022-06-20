
#include "scene/Mesh.hpp"

#include <cassert>
namespace jse::scene {

	using namespace math;

	Mesh::Mesh()
	{
		mode = DM_TRIANGLES;
	}

	Mesh::~Mesh()
	{
	}

	void Mesh::SetParameters(unsigned numPos, unsigned numIndices, const drawMode_t mode_)
	{
		if (numPrimitives > 0) return;

		this->mode = mode_;
		this->numPrimitives = numPos;
		this->numIndices = numIndices;
	}

}