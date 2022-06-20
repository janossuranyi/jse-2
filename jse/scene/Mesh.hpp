#ifndef JSE_SCENE_MESH_H
#define JSE_SCENE_MESH_H

#include <cstdint>
#include <vector>
#include "core/math/Vector.hpp"
#include "core/math/Matrix.hpp"
#include "core/io/MemoryBuffer.hpp"

namespace jse::scene {
	
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
	private:
		drawMode_t mode;
		int numPrimitives{ 0 };
		int numIndices{ 0 };
		int material{ -1 };
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
