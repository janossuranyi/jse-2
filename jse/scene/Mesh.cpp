
#include "scene/Mesh.hpp"

#include <cassert>
namespace jse::scene {

	using namespace core::math;

	Mesh::Mesh()
	{		
	}

	Mesh::~Mesh()
	{
		if (xyz)		delete[] xyz;
		if (normals)	delete[] normals;
		if (tangents)	delete[] tangents;
		if (st)			delete[] st;
		if (colors)		delete[] colors;
		if (indices)	delete[] indices;
	}

	void Mesh::AllocPositions(unsigned numPos, unsigned numIndices, const primitiveType_t type)
	{
		if (numPrimitives > 0) return;

		xyz = new vec3[numPos];
		indices = new triIndex_t[numIndices];

		this->numPrimitives = numPos;
		this->numIndices = numIndices;
	}

	void Mesh::AllocColors()
	{
		if (numPrimitives > 0 && !colors)
			colors = new vec3[numPrimitives];
	}
	void Mesh::AllocNormals()
	{
		if (numPrimitives > 0 && !normals)
			normals = new vec3[numPrimitives];
	}
	void Mesh::AllocTexCoords()
	{
		if (numPrimitives > 0 && !st)
			st = new vec2[numPrimitives];
	}
	void Mesh::AllocTangents()
	{
		if (numPrimitives > 0 && !tangents)
			tangents = new vec4[numPrimitives];
	}
	void Mesh::AllocColors()
	{
		if (numPrimitives > 0 && !colors)
			colors = new vec3[numPrimitives];
	}

}