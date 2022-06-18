#ifndef JSE_CORE_MATH_VECTOR_H
#define JSE_CORE_MATH_VECTOR_H

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace jse::core::math {

	using vec2 = glm::vec2;
	using vec3 = glm::vec3;
	using vec4 = glm::vec4;
	using quat = glm::quat;

	using ivec2 = glm::ivec2;
	using ivec3 = glm::ivec3;
	using ivec4 = glm::ivec4;

	inline float deg2rad(float p)
	{
		return glm::radians(p);
	}
	inline float rad2deg(float p)
	{
		return glm::degrees(p);
	}
	inline quat createQuaternion(const float rX, const float rY, const float rZ)
	{
		quat qx = glm::angleAxis(glm::radians(rX), vec3(1.f, 0.f, 0.f));
		quat qy = glm::angleAxis(glm::radians(rY), vec3(0.f, 1.f, 0.f));
		quat qz = glm::angleAxis(glm::radians(rZ), vec3(0.f, 0.f, 1.f));

		return qz * qy * qx;
	}
	template<class Ty>
	inline float dot(const Ty& v1, const Ty& v2)
	{
		return glm::dot(v1, v2);
	}
	template<class Ty>
	inline float distance(const Ty& v1, const Ty& v2)
	{
		return glm::distance(v1, v2);
	}
	template<class Ty>
	inline float lenght(const Ty& v)
	{
		return glm::length(v);
	}
	template<class Ty>
	inline Ty normalize(const Ty& v)
	{
		return glm::normalize(v);
	}
	template<class Ty>
	inline Ty cross(const Ty& v1, const Ty& v2)
	{
		return glm::cross(v1, v2);
	}
	template<class Ty>
	inline Ty reflect(const Ty& v1, const Ty& v2)
	{
		return glm::reflect(v1, v2);
	}
	template<class Ty>
	inline Ty refract(const Ty& I, const Ty& N, float eta)
	{
		return glm::refract(I, N, eta);
	}

}
#endif // !JSE_CORE_MATH_VECTOR_H
