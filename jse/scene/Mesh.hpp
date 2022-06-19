#ifndef JSE_SCENE_MESH_H
#define JSE_SCENE_MESH_H

#include <cstdint>
#include <vector>
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

		void SetMaterial(int material_);

		int GetNumPrimitives() const;
		int GetNumIndices() const;
		int GetMaterial() const;
		std::vector<core::math::vec3>& GetPositions();
		std::vector<core::math::vec3>& GetNormals();
		std::vector<core::math::vec3>& GetColors();
		std::vector<core::math::vec4>& GetTangents();
		std::vector<core::math::vec2>& GetTexCoords();
		std::vector<triIndex_t>& GetIndices();

		void SetLocalTransform(const core::math::mat4& mtx);
		const core::math::mat4& GetLocalTransform() const;
	private:
		primitiveType_t type;
		std::vector<core::math::vec3> xyz;
		std::vector<core::math::vec3> normals;
		std::vector<core::math::vec4> tangents;
		std::vector<core::math::vec2> st;
		std::vector<core::math::vec3> colors;
		std::vector<triIndex_t> indices;

		core::math::mat4 localTransform{ 1.0f };

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
	inline std::vector<core::math::vec3>& Mesh::GetColors()
	{
		return colors;
	}
	inline std::vector<core::math::vec3>& Mesh::GetPositions()
	{
		return xyz;
	}
	inline std::vector<core::math::vec3>& Mesh::GetNormals()
	{
		return normals;
	}
	inline std::vector<core::math::vec4>& Mesh::GetTangents()
	{
		return tangents;
	}
	inline std::vector<core::math::vec2>& Mesh::GetTexCoords()
	{
		return st;
	}
	inline std::vector<triIndex_t>& Mesh::GetIndices()
	{
		return indices;
	}
}

#endif // !JSE_SCENE_H
