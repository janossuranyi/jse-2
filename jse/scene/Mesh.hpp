#ifndef JSE_SCENE_MESH_H
#define JSE_SCENE_MESH_H

#include <cstdint>
#include <vector>
#include "core/math/Vector.hpp"
#include "core/math/Matrix.hpp"
#include "core/io/MemoryBuffer.hpp"
#include "graphics/DrawVert.hpp"

namespace jse {
	
	using triIndex_t = uint32_t;

	enum drawMode_t
	{
		DM_TRIANGLES,
		DM_POINTS,
		DM_LINES,
		DM_TRIANGLE_FAN,
		DM_TRIANGLE_STRIP,
		DM_LINE_STRIP,
		DM_LINE_LOOP
	};

	class Mesh
	{
	public:
		Mesh();
		~Mesh();

		void SetParameters(unsigned numPos, unsigned numIndices, const drawMode_t mode_);
		void SetMaterial(int material_);

		int GetNumPrimitives() const;
		int GetNumIndices() const;
		int GetMaterial() const;
		MemoryBuffer<vec2>& GetTexCoords() { return st; }
		MemoryBuffer<vec3>& GetPositions() { return xyz; };
		MemoryBuffer<vec3>& GetNormals() { return normals; }
		MemoryBuffer<vec4>& GetTangents() { return tangents; }
		MemoryBuffer<vec4>& GetColors() { return colors; }

		MemoryBuffer<unsigned short>& GetIndex16() { return sIndex; };
		MemoryBuffer<unsigned int>& GetIndex32() { return iIndex; };

		MemoryBuffer<DrawVert> CreateDrawVerts();
	private:
		drawMode_t mode;
		int numPrimitives{ 0 };
		int numIndices{ 0 };	
		int material{ -1 };

		MemoryBuffer<vec2> st;
		MemoryBuffer<vec3> xyz;
		MemoryBuffer<vec3> normals;
		MemoryBuffer<vec4> tangents;
		MemoryBuffer<vec4> colors;

		MemoryBuffer<unsigned short> sIndex;
		MemoryBuffer<unsigned int> iIndex;

	};

	inline int Mesh::GetMaterial() const
	{
		return material;
	}
	inline void Mesh::SetMaterial(int material_)
	{
		material = material_;
	}
	inline int Mesh::GetNumPrimitives() const
	{
		return numPrimitives;
	}
	inline int Mesh::GetNumIndices() const
	{
		return numIndices;
	}
}

#endif // !JSE_SCENE_H
