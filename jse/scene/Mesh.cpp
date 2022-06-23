
#include "scene/Mesh.hpp"

#include <cassert>
namespace jse {

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


	MemoryBuffer<DrawVert> Mesh::CreateDrawVerts()
	{
		MemoryBuffer<DrawVert> buf(numPrimitives * sizeof(DrawVert));

		for (int i = 0; i < numPrimitives; ++i)
		{
			DrawVert v;
			v.SetPosition( xyz[i] );
			v.SetNormal( normals[i] );
			v.SetTangent( tangents[i] );
			v.SetTextCoord(	st[i] );
			v.SetColor(vec4(0.0f));
			v.SetColor2(vec4(0.0f));
			buf[i] = v;
		}

		return buf;
	}


}