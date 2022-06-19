#ifndef JSE_SCENE_MESH_H
#define JSE_SCENE_MESH_H

#include <cstdint>

#include "core/math/Vector.hpp"
#include "core/math/Matrix.hpp"

namespace jse::scene {
	
	using triIndex_t = uint32_t;

	enum primitiveType_t
	{
		PT_TRIANGLES,
		PT_POINTS,
		PT_LINES,
		PT_TRIANGLE_FAN,
		PT_TRIANGLE_STRIP,
		PT_LINE_STRIP
	};

	class Mesh
	{
	public:
		Mesh();
		~Mesh();

		void AllocPositions(unsigned numPos, unsigned numIndices, const primitiveType_t type);
		void AllocNormals();
		void AllocTangents();
		void AllocTexCoords();
		void AllocColors();

		int GetNumPrimitives() const;
		int GetNumIndices() const;
		core::math::vec3* GetPositions();
		core::math::vec3* GetNormals();
		core::math::vec3* GetColors();
		core::math::vec4* GetTangents();
		core::math::vec2* GetTexCoords();
		triIndex_t* GetIndices();

		void SetLocalTransform(const core::math::mat4& mtx);
		const core::math::mat4& GetLocalTransform() const;
	private:
		primitiveType_t type;
		core::math::vec3* xyz{};
		core::math::vec3* normals{};
		core::math::vec4* tangents{};
		core::math::vec2* st{};
		core::math::vec3* colors{};
		triIndex_t* indices{};

		core::math::mat4 localTransform{ 1.0f };

		int numPrimitives{ 0 };
		int numIndices{ 0 };
	};

	inline const core::math::mat4& Mesh::GetLocalTransform() const
	{
		return localTransform;
	}
	inline void Mesh::SetLocalTransform(const core::math::mat4& mtx)
	{
		localTransform = mtx;
	}
	inline int Mesh::GetNumPrimitives() const
	{
		return numPrimitives;
	}
	inline int Mesh::GetNumIndices() const
	{
		return numIndices;
	}
	inline core::math::vec3* Mesh::GetColors()
	{
		return colors;
	}
	inline core::math::vec3* Mesh::GetPositions()
	{
		return xyz;
	}
	inline core::math::vec3* Mesh::GetNormals()
	{
		return normals;
	}
	inline core::math::vec4* Mesh::GetTangents()
	{
		return tangents;
	}
	inline core::math::vec2* Mesh::GetTexCoords()
	{
		return st;
	}
	inline triIndex_t* Mesh::GetIndices()
	{
		return indices;
	}
}

#endif // !JSE_SCENE_H
